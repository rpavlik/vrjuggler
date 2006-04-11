/*
 * VRJuggler
 *   Copyright (C) 1997,1998,1999,2000
 *   Iowa State University Research Foundation, Inc.
 *   All Rights Reserved
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
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile$
 * Date modified: $Date$
 * Version:       $Revision$
 * -----------------------------------------------------------------
 */


import PerfDataCollector;
import java.util.Vector;
import java.io.*;

public class Analyzer {

public static void main (String argv[]) throws IOException {
    int i;
    PerfDataCollector collector;
    int num;
    String name;
    boolean doanomaly = true;
    Vector data = new Vector();
    
    int preskip = 10;
    int postskip = 10;
    float anomalycutoff = 1.0f;

    String filename = null;
    for (i = 0; i < argv.length; i++) {
	//System.out.println (argv[i]);
	if (argv[i].equalsIgnoreCase ("-noanomaly")) {
	    doanomaly = false;
	}
	else if (argv[i].equalsIgnoreCase ("-skipfirst")) {
	    i++;
	    preskip = Integer.parseInt (argv[i]);
	}
	else if (argv[i].equalsIgnoreCase ("-skiplast")) {
	    i++;
	    postskip = Integer.parseInt (argv[i]);
	}
	else if (argv[i].equalsIgnoreCase ("-anomalycutoff")) {
	    i++;
	    anomalycutoff = (Float.valueOf (argv[i]).floatValue())/100.0f;
	}
	else {
	    filename = argv[i];
	}
    }

    if (filename == null) {
	System.out.println ("need name of data file");
	return;
    }
    
    FileReader r = new FileReader(filename);
    StreamTokenizer st = new StreamTokenizer(r);
    st.eolIsSignificant(false);
    st.quoteChar('"');

    // there's probably some streamtokenizer initialization to do...
    st.nextToken();
    //System.out.println (st.sval);

    for (;;) {
	st.nextToken();
	if (st.ttype == StreamTokenizer.TT_EOF)
	    break;
	if (st.ttype == StreamTokenizer.TT_WORD) {
	    //System.out.println ("token is " + st.ttype + " " + st.sval);
	    if (st.sval.equalsIgnoreCase ("PerfData1")) {
		st.nextToken();
		name = st.sval;
		st.nextToken();
		num = (int)st.nval;
		//System.out.println ("name is " + name + "\nnum is " + num);
		for (i = 0; i < data.size(); i++) {
		    collector = (PerfDataCollector)data.elementAt(i);
		    if (collector.name.equalsIgnoreCase(name)) {
			collector.read(st);
			break;
		    }
		}
		if (i == data.size()) {
		    collector = new PerfDataCollector(name, num);
		    data.addElement(collector);
		    //System.out.println ("about to read");
		    collector.read(st);
		    //System.out.println ("done read");
		}
	    }
	}
	
    }
    
    for (i = 0; i < data.size(); i++) {
	collector = (PerfDataCollector)data.elementAt(i);
	//System.out.println ("foo" + collector);
	//System.out.println ("------------------------");
	//System.out.println (collector.dumpData());
	System.out.println ("------------------------");
	System.out.println (collector.dumpAverages(preskip, postskip, doanomaly,anomalycutoff));
	System.out.println ("------------------------");
    }

}
    
    

};




