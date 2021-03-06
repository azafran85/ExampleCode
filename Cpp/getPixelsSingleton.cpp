#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <iostream>
#include <memory>


// g++ -std=c++14 getPixelsSingleton.cpp -lX11 -o frame2

class xPixelHandler
{
	private:
		static std::unique_ptr<xPixelHandler> instance;
		struct _cons {explicit _cons() = default; };
        Display* display;
        Window root;
        
	public:
		int width;
        int height;
      //  std::vector<unsigned int> Pixels;
        
		xPixelHandler(_cons)
        {
            display = XOpenDisplay(nullptr);
            root = DefaultRootWindow(display);
        }
        
		static std::unique_ptr<xPixelHandler> instanceFactory()
		{
			return std::make_unique<xPixelHandler>(_cons{});
		}

	static std::unique_ptr<xPixelHandler> &getInstance();
	~xPixelHandler()
    {
        
        XCloseDisplay(display);
    }
    
    int returnWidth()
    {
            

            XWindowAttributes attributes = {0};
            XGetWindowAttributes(display, root, &attributes);

            width = attributes.width;
            
            return width;
    }

    int returnHeight()
    {
        
            XWindowAttributes attributes = {0};
            XGetWindowAttributes(display, root, &attributes);

            height = attributes.height;
            
            return height;
    }
    
    void getPixels(std::vector<unsigned int>& Pixels, int& Width, int& Height)
    {
        
            XWindowAttributes attributes = {0};
            XGetWindowAttributes(display, root, &attributes);

            Width = attributes.width;
            Height = attributes.height;

            XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
            Pixels.resize(Width * Height * 4);

            memcpy(&Pixels[0], img->data, Pixels.size());
            
            XDestroyImage(img);
    }

};

std::unique_ptr<xPixelHandler> xPixelHandler::instance = NULL;

std::unique_ptr<xPixelHandler>& xPixelHandler::getInstance()
{
	if(instance == NULL)
	{
		instance = xPixelHandler::instanceFactory();
	}

	return instance;
}


int main()
{
    int Width = 0;
    int Height = 0;
    int Bpp = 0;
    std::vector<unsigned int> Pixels;

	std::unique_ptr<xPixelHandler> &p = xPixelHandler::getInstance();
  
    p->getPixels(Pixels, Width, Height);
    
    std::cout<<p->returnWidth() * p->returnHeight()<<std::endl;
    std::cout<<Pixels.size()<<std::endl;
        
    //for(auto& s : Pixels)
    //    std::cout<<s<<"\n";
   
    return 0;
}
