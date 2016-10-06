package com.Seg;


import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

import javax.xml.soap.Text;

import edu.stanford.nlp.ie.crf.CRFClassifier;
import edu.stanford.nlp.ie.AbstractSequenceClassifier;
import edu.stanford.nlp.ling.CoreLabel;
import edu.stanford.nlp.sequences.DocumentReaderAndWriter;
public class SegDemo {

  private static final String basedir = System.getProperty("SegDemo", "data");

  public static void main(String[] args) throws Exception {
    System.setOut(new PrintStream(System.out, true, "utf-8"));

    Properties props = new Properties();
    props.setProperty("sighanCorporaDict", basedir);
    props.setProperty("serDictionary", basedir + "/dict-chris6.ser.gz");
    if (args.length > 0) {
      props.setProperty("testFile", args[0]);
    }
    props.setProperty("inputEncoding", "UTF-8");
    props.setProperty("sighanPostProcessing", "true");

    CRFClassifier<CoreLabel> segmenter = new CRFClassifier<CoreLabel>(props);
    segmenter.loadClassifierNoExceptions(basedir + "/ctb.gz", props);
    for (String filename : args) {
      segmenter.classifyAndWriteAnswers(filename);
    }
    PrintWriter w = new PrintWriter("Stanford_word.txt");
    BufferedReader br=new BufferedReader(new InputStreamReader(new FileInputStream("sentence.txt"),"GBK"));  
    String line = null;  
    while ((line = br.readLine()) != null) 
    { 
        List<String> segmented = segmenter.segmentString(line);
        for(String s : segmented)
        {
             w.print(s);
             w.print("  ");
        }
        w.print('\n');
    }
    System.out.println("Complete the segmentation words");
    br.close();
    w.close();
  }
}
