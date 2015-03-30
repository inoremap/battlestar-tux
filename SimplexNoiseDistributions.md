## Procedural Content Generation with Simplex Noise ##

Battlestar T.U.X. uses Simplex procedural noise functions to generate much of the content.  There are several functions available to generate this noise, each with its own distribution of random noise.  The plots below demonstrate the behavior of each function.

The raw noise functions return a value in the interval [-1, 1] for all possible inputs.  The scaled noise functions theoretically return a value in the interval [loBound, hiBound], but the values loBound and hiBound almost never appear.

#  #
### Raw Noise ###
| **Raw Noise (0 - 100, 0.1 increments)** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/raw_0.1_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/raw_0.1_noise.png) | **Raw Noise (0 - 1000, 1.0 increments)** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/raw_1.0_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/raw_1.0_noise.png) |
|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

#  #
### Scaled Raw Noise ###
| **Scaled Raw Noise (loBound = 0, hiBound = 10)** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_noise.png) | **Scaled Raw Noise (loBound = 50, hiBound = 100)** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_50_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_50_noise.png) |
|:-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|

#  #
### Multi-Octave Noise ###
Multi-Octave noise is created by summing multiple passes of raw noise (the number of passes is called the number of octaves).  The contribution of each succeeding octave is determined by the persistence.  The larger the persistence, the more of each octave is included in the total.  As shown, multi-octave noise is necessary if you need a smooth distribution curve.

| **1 Octave, Persistence Irrelevant** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/1octaves_0.9persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/1octaves_0.9persist_noise.png) |
|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **2 Octaves, 0.1 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/2octaves_0.1persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/2octaves_0.1persist_noise.png) | **3 Octaves, 0.1 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/3octaves_0.1persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/3octaves_0.1persist_noise.png) |
| **4 Octaves, 0.1 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/4octaves_0.1persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/4octaves_0.1persist_noise.png) | **5 Octaves, 0.1 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/5octaves_0.1persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/5octaves_0.1persist_noise.png) |

| **2 Octaves, 0.5 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/2octaves_0.5persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/2octaves_0.5persist_noise.png) | **3 Octaves, 0.5 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/3octaves_0.5persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/3octaves_0.5persist_noise.png) |
|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **4 Octaves, 0.5 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/4octaves_0.5persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/4octaves_0.5persist_noise.png) | **5 Octaves, 0.5 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/5octaves_0.5persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/5octaves_0.5persist_noise.png) |

| **2 Octaves, 0.9 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/2octaves_0.9persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/2octaves_0.9persist_noise.png) | **3 Octaves, 0.9 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/3octaves_0.9persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/3octaves_0.9persist_noise.png) |
|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **4 Octaves, 0.9 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/4octaves_0.9persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/4octaves_0.9persist_noise.png) | **5 Octaves, 0.9 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/5octaves_0.9persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/5octaves_0.9persist_noise.png) |

#  #
### Scaled Multi-Octave Noise ###
| **2 Octaves, 0.1 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_2octaves_0.1persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_2octaves_0.1persist_noise.png) | **2 Octaves, 0.3 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_2octaves_0.3persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_2octaves_0.3persist_noise.png) |
|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **2 Octaves, 0.5 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_2octaves_0.5persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_2octaves_0.5persist_noise.png) | **2 Octaves, 0.7 Persistence** ![http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_2octaves_0.7persist_noise.png](http://wiki.battlestar-tux.googlecode.com/git/images/simplex_noise/scaled_10_2octaves_0.7persist_noise.png) |

#  #
These plots, and more, can be found in http://code.google.com/p/battlestar-tux/source/browse/images/simplex_noise/?repo=wiki

#  #
### References ###
> R Development Core Team (2007). R: A language and environment for
> statistical computing. R Foundation for Statistical Computing,
> Vienna, Austria. ISBN 3-900051-07-0, URL http://www.R-project.org.

> Stefan Gustavson's Explanation of Simplex Noise: http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf