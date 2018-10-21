import gifAnimation.*;

PImage img;
PrintWriter output;


int spaceX = 40;
int spaceY = 30;

int sizeX = 10;
int sizeY = 10;
  PImage[] animation;
void setup() {  
  size(380, 910);
  //img = loadImage("pumpkin.png");
  output = createWriter("gif-array.txt");
  frameRate(100);
  
  //nonLoopingGif.ignoreRepeat();
  // create the PImage array for the interactive display
  animation = Gif.getPImages(this, "ezgif.com-resize.gif");
  println(animation.length);
}

int imgIndex = 0;

void draw() {
  
  if (imgIndex >= animation.length)
    return;
  println("started");
  
  img = animation[imgIndex];
  imgIndex++;
  
  //output.println("rgbArray[10][42][3] = {");   
  output.println("{");
  
  //loadPixels(); 
  // Since we are going to access the image's pixels too  
  img.loadPixels(); 
  for (int x = 0; x < img.width; x++) {
     // go by column
    
     output.println("  {");
    //output.print("{");
    
    for (int y = 0; y < img.height; y++) {
      int loc = y*img.width + x;     
      
      // The functions red(), green(), and blue() pull out the 3 color components from a pixel.
      int r = int(red(img.pixels[loc]));
      int g = int(green(img.pixels[loc]));
      int b = int(blue(img.pixels[loc]));
      
      // Image Processing would go here
      // If we were to change the RGB values, we would do it here, before setting the pixel in the display window.
      //output.println("r"+r+",g"+g+",b"+b);
      output.println("    {"+r+","+g+","+b+"},");
      //output.print("{"+r+","+g+","+b+"},");      
      
      noStroke();
      fill(color(r*2,g*2,b*2));
      rect(x + (x*spaceX), y + (y*spaceY), sizeX, sizeY);
        
      // Set the display pixel to the image pixel
      //pixels[loc] =  color(r,g,b);          
    }
    
    output.println("  },");
    //output.print(" },");
    
  }
  //updatePixels();  
  
  
  //output.print("};");
  output.print("},");
  if (animation.length == (imgIndex +1)) {
    output.flush();
    output.close();
  }
}
