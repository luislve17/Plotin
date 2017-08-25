# Plotin
## Plug & use instructions:
Just paste the "plotin" and "PlotinData" folders in the same path as your project
<pre>
  * Path
    |-to
      |- my_project.cpp
      |- PlotinData (empty)
      |- plotin
        |-Plot.h
        |-Plot.cpp
        |-Plotin_types.h
</pre>

To import in "my_project" just add
```c++
#include "plotin/Plot.h"
```

To compile:
```
g++ my_project.cpp plotin/Plot.cpp
```

## Available methods (see examples)
* Plot scatters
* Plot curves
* Animate scatters

## Requirements
* Have gnuplot 5.0 patchlevel 3 installed

## Final notes
* **THIS MAY ONLY WORK ON LINUX**, other OS have not been tested.
