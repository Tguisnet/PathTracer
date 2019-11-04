# Pathtracer project

This is a basic PathTracer.

## Dependencies

OpenMesh - https://www.openmesh.org

Eigen - https://eigen.tuxfamily.org

LodePNG - https://lodev.org/lodepng/

JSON for Modern C++ (by nlohmann) - https://nlohmann.github.io/json/

## Authors

Thibault Guisnet and Anis Ladram, EPITA students (IMAGE 2020)

## Results
On the left, we have the image directly generated with our PathTracer, on the right we have the image after denoising (we used the Nvidia denoiser).

Classic BSDF (lambert BRDF, no BTDF) :

<a href="https://i.imgur.com/Epn5npZ.jpg"><img src="https://i.imgur.com/Epn5npZ.jpg" width="380"/></a>

Classic BSDF with more computing time :

<a href="https://i.imgur.com/HhoBAgK.jpg"><img src="https://i.imgur.com/HhoBAgK.jpg" width="380"/></a> <a href="https://i.imgur.com/aHfo1Cd.png"><img src="https://i.imgur.com/aHfo1Cd.png" width="380"/></a>

We add a mirror BSDF for the left rectangle :

<a href="https://i.imgur.com/wkW5XV9.jpg"><img src="https://i.imgur.com/wkW5XV9.jpg" width="380"/></a>

We add a mirror BSDF and we change our point of view :

<a href="https://i.imgur.com/KwHIpWn.jpg"><img src="https://i.imgur.com/KwHIpWn.jpg" width="380"/></a> <a href="https://i.imgur.com/VqL6CDN.png"><img src="https://i.imgur.com/VqL6CDN.png" width="380"/></a>

We try a metal BSDF for the left rectangle :

<a href="https://i.imgur.com/wTgaXA9.jpg"><img src="https://i.imgur.com/wTgaXA9.jpg" width="380"/></a> <a href="https://i.imgur.com/3vuDEjS.png"><img src="https://i.imgur.com/3vuDEjS.png" width="380"/></a>

We try a glass BSDF for the right cube, and a mirror BSDF on a sphere :

<a href="https://i.imgur.com/ed6Uopr.jpg"><img src="https://i.imgur.com/ed6Uopr.jpg" width="380"/></a> <a href="https://i.imgur.com/1nx0Mda.png"><img src="https://i.imgur.com/1nx0Mda.png" width="380"/></a>

We try the PathTracer on a more complicated obj :

<a href="https://i.imgur.com/3siKs9O.png"><img src="https://i.imgur.com/3siKs9O.png" width="380"/></a> <a href="https://i.imgur.com/x40qRtb.png"><img src="https://i.imgur.com/x40qRtb.png" width="380"/></a>

Finally, we try to render a complex scene :

<a href="https://i.imgur.com/ssfLqrJ.png"><img src="https://i.imgur.com/ssfLqrJ.png" width="380"/></a> <a href="https://i.imgur.com/6MjMl08.png"><img src="https://i.imgur.com/6MjMl08.png" width="380"/></a>