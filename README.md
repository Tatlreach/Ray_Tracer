### Goal
I created this Ray Tracer to familiarize myself with modern offline rendering algorthms. I wrote this in conjunction with the book [Ray Tracing in One Weekend](https://www.amazon.com/Ray-Tracing-Weekend-Minibooks-Book-ebook/dp/B01B5AODD8).

### Criteria

* Render Time
* Image Quality
* Code Cleanliness

### Functionality

The Ray Tracer renders 1 Computer Generated Image and writes it to a .ppm file. To do so, it creates a scene with a couple of spheres and 1 camera. Then it sends out rays that go from a Camera through a virtual screen in the scene. Each ray corresponds to a pixel on the screen. The spheres each ray contacts affects how it changes direction and what color is calculated. Specifically, this is done in each sphere's material. The rays continue bouncing around the spheres until it misses all spheres.

### Example Image

See above or follow this to the [early_example.png](https://github.com/Tatlreach/Ray_Tracer/blob/master/early_example.png)

### Run Locally

* Download & run the executable.
* Open "spheres_image.ppm"

### Have Feedback?

Feel free to message me any comment or question. I'm always looking to improve my code, algorithms, & design.

### Potential Future Plans

* Create a Menu with multiple scenes to be rendered
* Add Options to the Menu to select different resolutions & sample counts
* Estimate render time & scale the value to the resolution/sample level