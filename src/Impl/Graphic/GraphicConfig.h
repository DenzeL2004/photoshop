#ifndef _GRAPHIC_CONFIG_H_
#define _GRAPHIC_CONFIG_H_

#include "Plug/Graphics.h"
#include "Plug/Color.h"

namespace plug
{
    static const plug::Color White  = plug::Color(255, 255, 255, 255);
    static const plug::Color Black  = plug::Color(0, 0, 0, 255);

    static const plug::Color Red    = plug::Color(255, 0, 0, 255);
    static const plug::Color Green  = plug::Color(0, 255, 0, 255);
    static const plug::Color Blue   = plug::Color(0, 0, 255, 255);

    static const plug::Color Transparent = plug::Color(0, 0, 0, 0);

    static const size_t Symbol_width  = 7ul;
    static const size_t Symbol_height = 7ul;

    static const bool Unknown[Symbol_width * Symbol_height] = 
                                {
                                    0, 1, 0, 1, 0, 1, 0,                                     
                                    0, 0, 1, 0, 1, 0, 0,                                     
                                    0, 1, 0, 1, 0, 1, 0,                                     
                                    0, 0, 1, 0, 1, 0, 0,                                     
                                    0, 1, 0, 1, 0, 1, 0,                                     
                                    0, 0, 1, 0, 1, 0, 0,                                     
                                    0, 1, 0, 1, 0, 1, 0                                         
                                };

    static const bool Numbers[][Symbol_width * Symbol_height] = 
                                {
                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },  

                                    {   
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 1, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0
                                    },   

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 1, 0, 0, 0, 0,                                     
                                        0, 0, 1, 0, 0, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },      

                                    {   
                                        0, 0, 1, 1, 0, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 0, 0, 0
                                    },     

                                    {   
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0
                                    },  

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 1, 0, 0, 0, 0,                                     
                                        0, 0, 1, 0, 0, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },      

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 1, 0, 0, 0, 0,                                     
                                        0, 0, 1, 0, 0, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },         

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0
                                    },     

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },     

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0
                                    },        
                                };

    static const bool Question_mark[Symbol_width * Symbol_height] = 
                                {
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 1, 0, 1, 0, 0,                                     
                                    0, 0, 0, 0, 1, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0  
                                };
    
    static const bool Exclamation_mark[Symbol_width * Symbol_height] = 
                                {
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0  
                                };

    static const bool Dot[Symbol_width * Symbol_height] = 
                                {
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0  
                                };

    static const bool Plus[Symbol_width * Symbol_height] = 
                                {
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 1, 1, 1, 1, 1, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0  
                                };

    static const bool Slash[Symbol_width * Symbol_height] = 
                                {
                                    0, 0, 0, 0, 1, 0, 0,                                     
                                    0, 0, 0, 0, 1, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 0, 1, 0, 0, 0,                                     
                                    0, 0, 1, 0, 0, 0, 0,                                     
                                    0, 0, 1, 0, 0, 0, 0  
                                };

    static const bool Space[Symbol_width * Symbol_height] = 
                                {
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0,                                     
                                    0, 0, 0, 0, 0, 0, 0  
                                };

    static const bool Letters[][Symbol_width * Symbol_height] = 
                                {
                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 1, 1, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0
                                    },   

                                    {   
                                        0, 1, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 1, 1, 0, 0
                                    },      

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },     

                                    {   
                                        0, 1, 1, 1, 0, 0, 0,                                     
                                        0, 1, 0, 0, 1, 0, 0,                                     
                                        0, 1, 0, 0, 1, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 1, 1, 0,                                     
                                        0, 1, 0, 0, 1, 0, 0,                                     
                                        0, 1, 1, 1, 0, 0, 0
                                    },  

                                    {   
                                        0, 1, 1, 1, 1, 1, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 1, 1, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 1, 1, 1, 1, 0
                                    },      

                                    {   
                                        0, 1, 1, 1, 1, 1, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 1, 1, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0
                                    },         

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 1, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },     

                                    {   
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 1, 1, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0
                                    },     

                                    {   
                                        0, 1, 1, 1, 1, 1, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 1, 1, 1, 1, 1, 0
                                    },    

                                    {   
                                        0, 1, 1, 1, 1, 1, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 1, 0, 1, 0, 0, 0,                                     
                                        0, 0, 1, 0, 0, 0, 0
                                    },

                                    {   
                                        0, 1, 0, 0, 1, 0, 0,                                     
                                        0, 1, 0, 1, 0, 0, 0,                                     
                                        0, 1, 0, 1, 0, 0, 0,                                     
                                        0, 1, 1, 0, 0, 0, 0,                                     
                                        0, 1, 0, 1, 0, 0, 0,                                     
                                        0, 1, 0, 0, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0
                                    },      

                                    {   
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 1, 1, 1, 1, 0
                                    },   

                                    {   
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 0, 1, 1, 0,                                     
                                        0, 1, 0, 1, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0
                                    },      

                                    {   
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 0, 0, 1, 0,                                     
                                        0, 1, 0, 1, 0, 1, 0,                                     
                                        0, 1, 0, 1, 0, 1, 0,                                     
                                        0, 1, 0, 1, 0, 1, 0,                                     
                                        0, 1, 0, 0, 1, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0
                                    },  

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },  

                                    {   
                                        0, 1, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0
                                    },          

                                    {   
                                        0, 0, 1, 1, 0, 0, 0,                                     
                                        0, 1, 0, 0, 1, 0, 0,                                     
                                        0, 1, 0, 0, 1, 0, 0,                                     
                                        0, 1, 0, 0, 1, 0, 0,                                     
                                        0, 1, 0, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 1, 0, 0,                                     
                                        0, 0, 1, 1, 0, 1, 0
                                    },       

                                    {   
                                        0, 1, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 1, 1, 0, 0,                                     
                                        0, 1, 1, 0, 0, 0, 0,                                     
                                        0, 1, 0, 1, 0, 0, 0,                                     
                                        0, 1, 0, 0, 1, 0, 0
                                    },   

                                    {   
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0,                                     
                                        0, 0, 0, 0, 0, 1, 0,                                     
                                        0, 0, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 1, 1, 0, 0
                                    },     

                                    {   
                                        0, 1, 1, 1, 1, 1, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0
                                    },    

                                    {   
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 0, 1, 1, 1, 0, 0
                                    },    

                                    {   
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0
                                    },    

                                    {   
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 0, 1, 0, 1, 0,                                     
                                        0, 1, 0, 1, 0, 1, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0
                                    }, 

                                    {   
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 1, 1, 0, 1, 1, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 1, 1, 0, 1, 1, 0,                                     
                                        0, 1, 0, 0, 0, 1, 0
                                    },    

                                    {   
                                        0, 1, 0, 0, 0, 1, 0,                                     
                                        0, 0, 1, 0, 1, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0
                                    }, 

                                    {   
                                        0, 1, 1, 1, 1, 1, 0,                                     
                                        0, 0, 0, 0, 0, 1, 0,                                     
                                        0, 0, 0, 0, 1, 0, 0,                                     
                                        0, 0, 0, 1, 0, 0, 0,                                     
                                        0, 0, 1, 0, 0, 0, 0,                                     
                                        0, 1, 0, 0, 0, 0, 0,                                     
                                        0, 1, 1, 1, 1, 1, 0
                                    }, 
                                };
                            
};


#endif