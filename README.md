## Image visualiser tool

This is work in progress tool I build for debuggin problems image processing. It aims to extedn `cv::imshow`
It is very crude, but works fine for the purposes I use it, so for now I do not plan on making it less horrible.

It has three main funcionalities:
 - Hold right click and move up/down with the mouse to change zoom
 - Hold middle button and move mouse around to move around the zoomed window
 - Left click to call a predefined by you callback

Issues:
- Huge memory leak, lol - this one I'll fix sometime before 2020
- Zoom is written so badly... so badly... maaaybe I'll fix it when fixing the zoom
- Right click save the previous view, no sure how I was done - yes, before 2020
- The documentation is lacking
