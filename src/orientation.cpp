#include <baseapi.h>
#include <allheaders.h>
#include <publictypes.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char **argv)
{  
 
  const char* inputfile = "";
  tesseract::Orientation orientation;
  tesseract::WritingDirection direction;
  tesseract::TextlineOrder order;
  float deskew_angle;
  int count;
  string outfile = "out.txt";
  if(argc < 2)
  {
    printf("Usage is Orientation fileName ");
    exit(-1);
  }
  
  
  for( count = 0; count < argc; count++ )
  {
     switch (count)
     {
	case 1: 		
	 	  inputfile = argv[count];                
    	        break;
	/*case 2:                
		  outfile = argv[count];
    	        break;*/
     }          
  }

  try
  { 
          ifstream ifile(inputfile);
          if(!ifile)
          {
            printf("Please check if file present with this name");
            exit(-1);
          }  

	  PIX *image = pixRead(inputfile);
	  tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
	  api->Init(NULL,"eng");
	  //if (!api->SetVariable("min_orientation_margin","6"))
          //  printf("Setting variable failed!!!\n");
	  api->SetPageSegMode(tesseract::PSM_AUTO_OSD);
	  api->SetImage(image);
	  api->Recognize(0);
	 
	  tesseract::PageIterator* it =  api->AnalyseLayout();
	  it->Orientation(&orientation, &direction, &order, &deskew_angle);
	  //printf("Orientation: %d;\nWritingDirection: %d\nTextlineOrder: %d\n" \
	  // 	 "Deskew angle: %.4f\n",
	  //	 orientation, direction, order, deskew_angle);

	 
	  api->End();
	  //delete [] outText;
	  pixDestroy(&image);
	  return orientation;
  }
  catch(int e)
  {
    printf("Please check if the image file is present & given with proper parameters");
    exit(-1);
  }
}
