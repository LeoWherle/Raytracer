# Raytracer
- **Contributors:**
  - [Léo Wehrle - Rentmeister](https://github.com/leoWherle)
  - [Théodore Magna](https://github.com/TheodoreEpitech)
  - [Yanis Moyon](https://github.com/Kl0ups)
  - [Alberic Flour De Saegher](https://github.com/Albe2)

## Description



## Install
```bash
./build.sh release # to build as release
./build.sh debug # to build as debug
```

## Documentation
You can read the documentation by navigating to the `gh-pages` branch and opening the `index.html` file in your browser.


## Usage
```bash
./raytracer [scene_file]
```

## Result examples

![Result](assets/render/render.png)


### Obj models
***4000 triangles monkey***

![Model](assets/render/monkey.png)
```
render time = ~1h30
ray per pixel = 1 000
max depth = 30
```

-------
![Model](assets/render/monkey_12h.png)
```
render time = ~12h
ray per pixel = 30 000
max depth = 100
```


## UML
![UML](assets/plantuml/plantuml.svg)
