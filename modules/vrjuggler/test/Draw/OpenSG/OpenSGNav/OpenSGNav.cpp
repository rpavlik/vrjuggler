#include <vrj/vrjConfig.h>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <vrj/Math/Vec3.h>
#include <vrj/Math/Coord.h>

#include <OpenSGNav.h>

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGImageFileType.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGLogoData.h>
#include <OpenSG/OSGThread.h>
#include <OpenSG/OSGMPBase.h>

OSG::UInt32 OpenSGNav::OSG_MAIN_ASPECT_ID=0;

// Handle any initialization needed before API
void OpenSGNav::init()
{
   vrj::OpenSGApp::init();      // Call base class init

   // XXX: Complete
   // if(!osgInitAlreadyCalled())
   OSG::osgInit(0,0);                  // Binds to primordial thread
   OpenSGNav::OSG_MAIN_ASPECT_ID = OSG::Thread::getAspect();   // Gets the base aspect id to use
}

void OpenSGNav::contextInit()
{
   context_data* c_data = &(*mContextData);

   // Check for thread initialized
   if(!c_data->mContextThreadInitialized)
   {
      c_data->mContextThreadInitialized = true;

      char thread_name_buffer[255];
      sprintf(thread_name_buffer, "vprThread:%d", vpr::Thread::self()->getTID());
      c_data->mOsgThread = OSG::ExternalThread::get(thread_name_buffer);
      c_data->mOsgThread->initialize(OSG_MAIN_ASPECT_ID);     // XXX: In future this must be different thread
   }

   // Allocate OpenSG stuff
   c_data->mWin = OSG::PassiveWindow::create();
   c_data->mCameraCartNode = OSG::Node::create();
   c_data->mCameraCartTransform = OSG::Transform::create();
   c_data->mCamera = OSG::PerspectiveCamera::create();

   // Setup the cart, set internal transform node
   OSG::beginEditCP(c_data->mCameraCartNode);
      c_data->mCameraCartNode->setCore(c_data->mCameraCartTransform);
   OSG::endEditCP(c_data->mCameraCartNode);

   // Setup the camera
   OSG::beginEditCP(c_data->mCamera);
      c_data->mCamera->setBeacon (c_data->mCameraCartNode);
      c_data->mCamera->setFov    (OSG::deg2rad(60.));
      c_data->mCamera->setNear   (0.1);
      c_data->mCamera->setFar    (10000);
   OSG::endEditCP(c_data->mCamera);

   //vjOSGApp::contextInit();
   initGLState();
}


void OpenSGNav::draw()
{
   /*
    std::cout << "OpenSGNav::draw called\n";
    vrj::GlDrawManager* drawMan = dynamic_cast<vrj::GlDrawManager*> ( this->getDrawManager() );
    vprASSERT(drawMan != NULL);
    vrj::GlUserData* userData = drawMan->currentUserData();

    // Copy the matrix
    vrj::Projection* project = userData->getProjection();
    float * vj_proj_view_mat = project->mViewMat.getFloatPtr();
    OSGMat.setValue(vj_proj_view_mat);
    */

/*	//Get the frustrum
	vjFrustum frustum = project->mFrustum;
	
    //Reset the camera
    the_cam->home();

    //Set the frustrum (this is set with the matrix below)
    float near_val = frustum[vjFrustum::VJ_NEAR];
    the_cam->setFrustum(frustum[vjFrustum::VJ_LEFT]*near_val,   frustum[vjFrustum::VJ_RIGHT]*near_val,
                      frustum[vjFrustum::VJ_BOTTOM]*near_val,  frustum[vjFrustum::VJ_TOP]*near_val,
                      frustum[vjFrustum::VJ_NEAR],             frustum[vjFrustum::VJ_FAR]);
	
    //Set the look at
    the_cam->attachTransform(osg::Camera::MODEL_TO_EYE, &osgMat);*/
    /*
    OSGMat.setValue(1.0f,0.0f,0.0f,0.0f,
                    0.0f,1.0f,0.0f,0.0f,
                    0.0f,0.0f,1.0f,0.0f,
                    0.0f,0.0f,0.0f,1.0f);
                    */

    /*
    _cart->getSFMatrix()->setValue(OSGMat);
    updateHighlight();
    */
    //vjOSGApp::draw();
    std::cout << "OpenSGNav::draw called\n";

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     // Set material color
   float onyx_red = 59.0f/255.0f;
   float onyx_blue = 57.0f/255.0f;
   GLfloat mat_ambient[] = { onyx_red, 0.0, onyx_blue, 1.0};
   GLfloat mat_diffuse[] = { onyx_red, 0.0, onyx_blue, 1.0};
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = { 50.0};

   glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
   glMaterialfv( GL_FRONT,  GL_DIFFUSE, mat_diffuse );
   glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
   glMaterialfv( GL_FRONT,  GL_SHININESS, mat_shininess );
   //glColor4f(1.0, 1.0, 1.0, 1.0);

    //glLoadIdentity();
   glPushMatrix();
      glTranslatef(-1.5f,0.0f,6.0f);
       glBegin(GL_TRIANGLES);
         glVertex3f(0.0f,1.0f,0.0f);
         glVertex3f(-1.0f,-1.0f,0.0f);
         glVertex3f(1.0f,-1.0f,0.0f);
       glEnd();
   glPopMatrix();
}

void OpenSGNav::preFrame()
{
    //std::cout << "OpenSGNav::preFrame called\n";
    //move the model around
}

void OpenSGNav::bufferPreDraw()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenSGNav::initGLState()
{
    std::cout << "OpenSGNav::initGLState called\n";
    /*
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    glPixelStorei( GL_PACK_ALIGNMENT, 1 );
    */

    GLfloat light0_ambient[] = { .2,  .2,  .2,  1.0};
   GLfloat light0_diffuse[] = { 1.0,  1.0,  1.0,  1.0};
   GLfloat light0_specular[] = { 1.0,  1.0,  1.0,  1.0};
   GLfloat light0_position[] = {6.0, 6,0, 6.0, 1.0};

   glLightfv(GL_LIGHT0, GL_AMBIENT,  light0_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE,  light0_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR,  light0_specular);
   glLightfv(GL_LIGHT0, GL_POSITION,  light0_position);

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_COLOR_MATERIAL);
   glShadeModel(GL_SMOOTH);

   glMatrixMode(GL_MODELVIEW);

}

void OpenSGNav::initRenderer()
{
   std::cout << "OpenSGNav::initRenderer called\n";

    //the rendering action
    mRenderAction = OSG::RenderAction::create();

    mRoot = OSG::Node::create();
    mRootGroupCore = OSG::Group::create();

    OSG::addRefCP(mRoot);
    OSG::beginEditCP(mRoot);
      mRoot->setCore(mRootGroupCore);
    OSG::endEditCP(mRoot);

    std::cout << "OpenSGNav::initRenderer finished.\n";
}

void OpenSGNav::initScene(void)
{
   std::cout << "OpenSGNav::initScene called\n";
   std::string wand("VJWand");
   mWand.init(wand);

   // Load a graph
   if (1)
    {
        std::cout << "OpenSGNav::myInit beforetorusmake\n";
        mSceneRoot = OSG::makeTorus(.5, 2, 16, 16);
        std::cout << "OpenSGNav::myInit aftertorusmake\n";
    }
    else
    {
       std::cout << "OpenSGNav::myInit: Loading [" << mFileToLoad.c_str() << "]\n";
       mSceneRoot = OSG::SceneFileHandler::the().read((OSG::Char8 *)(mFileToLoad.c_str()));
    }
    std::cout << "OpenSGNav::myInit before RenderAction::create()\n";

    // -- light node --> light cart
    //the camera and light beacon
    mLightNode = OSG::Node::create();
    mLightCart = OSG::Node::create();
    OSG::DirectionalLightPtr light_core = OSG::DirectionalLight::create();
    OSG::TransformPtr cart_core = OSG::Transform::create();

    // Setup light cart node
    OSG::beginEditCP(mLightCart);
      mLightCart->setCore(cart_core);
    OSG::endEditCP(mLightCart);

    OSG::addRefCP(mLightNode);
    OSG::beginEditCP(mLightNode);
      mLightNode->setCore(light_core);
      mLightNode->addChild(mLightCart);
    OSG::endEditCP(mLightNode);

    OSG::beginEditCP(light_core);
      light_core->setAmbient   (.3, .3, .3, 1);
      light_core->setDiffuse   ( 1,  1,  1, 1);
      light_core->setSpecular  ( 1,  1,  1, 1);
      light_core->setDirection ( 0,  0,  1);
      light_core->setBeacon    (mLightNode);
    OSG::endEditCP(light_core);

    OSG::addRefCP(mSceneRoot);
    OSG::beginEditCP(mSceneRoot);
      mSceneRoot->addChild(mLightNode);
    OSG::endEditCP(mSceneRoot);

    std::cout << "OpenSGNav::initScene finished\n";
}

