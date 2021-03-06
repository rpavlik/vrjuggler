/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2010 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

package org.vrjuggler.vrjconfig.customeditors.display_window;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.util.*;
import javax.swing.*;

import org.vrjuggler.jccl.config.*;
import org.vrjuggler.jccl.config.event.*;
import org.vrjuggler.vrjconfig.commoneditors.Placer;
import org.vrjuggler.vrjconfig.commoneditors.placer.*;


/**
 * A component suitable for placing viewports within a display window.  This
 * class holds a single configuration element (type display_window) and
 * operates on the viewports contained therein.
 */
public class ViewportPlacer
   extends JPanel
   implements EditorConstants
{
   public ViewportPlacer(Dimension desktopSize, ConfigContext ctx,
                         ConfigElement elt)
   {
      model = new ViewportPlacerModel(desktopSize, ctx, elt);

      try
      {
         jbInit();
      }
      catch(Exception e)
      {
         e.printStackTrace();
      }

      // Setup the viewport placer.
      wndPlacer.setModel(model);
      wndPlacer.setRenderer(new ViewportRenderer());
   }

   public void setDesktopSize(Dimension desktopSize)
   {
      model.setDesktopSize(desktopSize);
   }

   public Dimension getDesktopSize()
   {
      return model.getDesktopSize();
   }

   /**
    * Gets the currently selected viewport configuration element.
    *
    * @return  the config element for the currently selected viewport;
    *          null if nothing is selected
    */
   public ConfigElement getSelectedViewport()
   {
      return (ConfigElement)wndPlacer.getSelectedValue();
   }

   /**
    * Gets the placer used internally by this viewport placer.
    */
   public Placer getPlacer()
   {
      return wndPlacer;
   }

   /**
    * Automatically generated JBuilder GUI init.
    */
   private void jbInit()
      throws Exception
   {
      this.setLayout(baseLayout);
      wndPlacer.setBorder(BorderFactory.createEtchedBorder());
      this.add(wndPlacer, BorderLayout.CENTER);
   }

   //--- JBuilder GUI variables ---//
   private BorderLayout baseLayout = new BorderLayout();

   /**
    * Our window placer.
    */
   private Placer wndPlacer = new Placer();

   /**
    * The data model for our window placer.
    */
   private ViewportPlacerModel model = null;

   /**
    * A specialized renderer for displays in the placer component.
    */
   class ViewportRenderer
      extends JPanel
      implements PlacerRenderer
   {
      private Placer placer;
      private int index;
      private boolean selected;
      private ImageIcon surfaceIcon, scaledSurfaceIcon;
      private ImageIcon simIcon, scaledSimIcon;

      public ViewportRenderer()
      {
         ClassLoader loader = getClass().getClassLoader();
         surfaceIcon =
            new ImageIcon(loader.getResource(IMAGE_BASE +
                                             "/vrjuggler-surface-viewport.png"));
         simIcon =
            new ImageIcon(loader.getResource(IMAGE_BASE +
                                             "/vrjuggler-sim-viewport.png"));
         scaledSurfaceIcon = new ImageIcon();
         scaledSimIcon     = new ImageIcon();
      }

      public Component getPlacerRendererComponent(Placer placer,
                                                  Object value,
                                                  boolean selected,
                                                  boolean focused,
                                                  int index)
      {
         this.placer = placer;
         this.index = index;
         this.selected = selected;
         if (selected)
         {
            setForeground(placer.getSelectionForeground());
            setBackground(placer.getSelectionBackground());
         }
         else
         {
            setForeground(placer.getSelectionBackground());
            setBackground(placer.getSelectionForeground());
         }

         return this;
      }

      public void paintComponent(Graphics g)
      {
         super.paintComponent(g);
         if (placer != null && index >= 0)
         {
            Dimension dim = placer.getModel().getSizeOf(index);

            ImageIcon icon, scaled_icon;

            // XXX: Come up with a cleaner way to do this.
            if ( ((ConfigElement) placer.getModel().getElement(index)).getDefinition().getToken().equals(SURFACE_VIEWPORT_TYPE) )
            {
               icon = surfaceIcon;
               scaled_icon = scaledSurfaceIcon;
            }
            else
            {
               icon = simIcon;
               scaled_icon = scaledSimIcon;
            }

            // Check if we need to update the scaled image
            Image img = scaled_icon.getImage();
            if ((scaled_icon.getIconWidth() != dim.width) ||
                (scaled_icon.getIconHeight() != dim.height))
            {
               img = icon.getImage().getScaledInstance(dim.width, dim.height,
                                                       Image.SCALE_DEFAULT);
               scaled_icon.setImage(img);
            }

            // Sanity check in case our scale failed
            if (img != null)
            {
               g.drawImage(img, 0, 0, null);
            }

            // Highlight the window nicely
            if (selected)
            {
               g.setColor(getBackground());
            }
            else
            {
               g.setColor(Color.white);
            }

            g.drawRect(0, 0, dim.width - 1, dim.height - 1);
            g.fillRect(0, 0, dim.width, 3);
         }
      }
   }
}

/**
 * A specialized placer model for our viewports.
 */
class ViewportPlacerModel
   extends AbstractPlacerModel
{
   public ViewportPlacerModel(Dimension desktopSize, ConfigContext ctx,
                              ConfigElement elt)
   {
      mDesktopSize = desktopSize;
      mContext        = ctx;
      mDisplayElement = elt;
      mDisplayElement.addConfigElementListener(mChangeListener);

      Iterator i;
      for ( i = elt.getPropertyValues("simulator_viewports").iterator(); i.hasNext(); )
      {
         mViewports.add(i.next());
      }

      for ( i = elt.getPropertyValues("surface_viewports").iterator(); i.hasNext(); )
      {
         mViewports.add(i.next());
      }
   }

   public Object getElement(int idx)
   {
      return mViewports.get(idx);
   }

   public int getIndexOf(Object obj)
   {
      return mViewports.indexOf(obj);
   }

   public Object getElementAt(Point pt)
   {
      int idx = getIndexOfElementAt(pt);
      if (idx != -1)
      {
         return getElement(idx);
      }
      return null;
   }

   public int getIndexOfElementAt(Point pt)
   {
      for ( int i = 0; i < mViewports.size(); ++i )
      {
         Point pos = getLocationOf(i);
         Dimension dim = getSizeOf(i);
         if (pt.x >= pos.x && pt.y >= pos.y &&
             pt.x < (pos.x + dim.width) && pt.y < (pos.y + dim.height))
         {
            return i;
         }
      }
      return -1;
   }

   public Dimension getSizeOf(int idx)
   {
      ConfigElement vp_elt = (ConfigElement) getElement(idx);

      double vp_width  = ((Number) vp_elt.getProperty("size", 0)).doubleValue();
      double vp_height = ((Number) vp_elt.getProperty("size", 1)).doubleValue();

      if ( vp_width > 1.0 )
      {
         vp_width = 1.0;
      }

      if ( vp_height > 1.0 )
      {
         vp_height = 1.0;
      }

      double width = vp_width * mDesktopSize.getWidth();
      double height = vp_height * mDesktopSize.getHeight();

      return new Dimension((int) width, (int) height);
   }

   public void setSizeOf(int idx, Dimension size)
   {
      ConfigElement vp_elt = (ConfigElement) getElement(idx);
      double vp_width  = (double) size.width / mDesktopSize.getWidth();
      double vp_height = (double) size.height / mDesktopSize.getHeight();

      if ( vp_width > 1.0 )
      {
         vp_width = 1.0;
      }

      if ( vp_height > 1.0 )
      {
         vp_height = 1.0;
      }

      vp_elt.setProperty("size", 0, new Double(vp_width), mContext);
      vp_elt.setProperty("size", 1, new Double(vp_height), mContext);
   }

   public Point getLocationOf(int idx)
   {
      ConfigElement vp_elt = (ConfigElement) getElement(idx);
      double x = ((Number) vp_elt.getProperty("origin", 0)).doubleValue() * mDesktopSize.getWidth();
      double y = ((Number) vp_elt.getProperty("origin", 1)).doubleValue() * mDesktopSize.getHeight();

      // Convert y from Juggler coords (bottom left is origin)
      double height =
         ((Number) vp_elt.getProperty("size", 1)).doubleValue() * mDesktopSize.getHeight();
      y = mDesktopSize.getHeight() - y - height;
      return new Point((int) x, (int) y);
   }

   public void setLocationOf(int idx, Point pt)
   {
      ConfigElement vp_elt = (ConfigElement)getElement(idx);

      // Convert y to Juggler coords (bottom left is origin)
      double height =
         ((Number) vp_elt.getProperty("size", 1)).doubleValue() * mDesktopSize.getHeight();
      double y = mDesktopSize.height - pt.y - height;

      double vp_origin_x = (double) pt.x / mDesktopSize.getWidth();
      double vp_origin_y = y / mDesktopSize.getHeight();

      if ( vp_origin_x < 0.0 )
      {
         vp_origin_x = 0.0;
      }

      if ( vp_origin_y < 0.0 )
      {
         vp_origin_y = 0.0;
      }

      vp_elt.setProperty("origin", 0, new Double(vp_origin_x), mContext);
      vp_elt.setProperty("origin", 1, new Double(vp_origin_y), mContext);
   }

   public void moveToFront(int idx)
   {
      // remove and reinsert at the front.
      mViewports.add(0, mViewports.remove(idx));
   }

   public int getSize()
   {
      return mViewports.size();
   }

   public Dimension getDesktopSize()
   {
      return mDesktopSize;
   }

   public void setDesktopSize(Dimension desktopSize)
   {
      mDesktopSize = desktopSize;
      fireDesktopSizeChanged();
   }

   private ConfigContext mContext        = null;
   private ConfigElement mDisplayElement = null;

   /**
    * The list of viewports (both surface and simulator) in this display window.
    */
   private List mViewports = new ArrayList();

   /** The size of the desktop in this model. */
   private Dimension mDesktopSize;

   /** The custom listener for changes to the displays. */
   private ChangeListener mChangeListener = new ChangeListener();

   private class ChangeListener
      extends ConfigElementAdapter
   {
      /**
       * Called whenever one of the displays contained within the model changes.
       */
      public void nameChanged(ConfigElementEvent evt)
      {
         int idx = getIndexOf(evt.getSource());
         if (idx != -1)
         {
            fireItemsChanged(new int[] { idx });
         }
      }

      public void propertyValueAdded(ConfigElementEvent event)
      {
         if ( event.getProperty().equals("simulator_viewports") ||
              event.getProperty().equals("surface_viewports") )
         {
            mViewports.add(0, event.getValue());
            fireItemsInserted(new int[] { 0 });
         }
      }

      public void propertyValueRemoved(ConfigElementEvent event)
      {
         if ( event.getProperty().equals("simulator_viewports") ||
              event.getProperty().equals("surface_viewports") )
         {
            int idx = getIndexOf(event.getValue());
            if (idx != -1)
            {
               mViewports.remove(idx);
               fireItemsRemoved(new int[] { idx },
                                new Object[] { event.getValue() });
            }
         }
      }
   }
}
