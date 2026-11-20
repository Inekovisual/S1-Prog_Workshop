# 🐣 S1 | Prog: Workshop

# Rapport de projet 

## Ne garder que le vert
![alt text](output/keep_green_only.png)

## Échanger les canaux
![alt text](output/channels_swap.png)

## Noir & Blanc
![alt text](output/black_and_white.png)

## Négatif
![alt text](output/negative.png)

## Dégradé
![alt text](output/color_gradient.png)

## Miroir
Au départ, quand je lançais mon programme, l’image restait la même alors que j’inversais bien les pixels. C’était parce que j’appliquais le `swap` sur toute la largeur/hauteur, ce qui annulait l’inversion en remettant les pixels à leur place d’origine. J’ai donc divisé la boucle par 2.

![alt text](output/mirror.png)

## Image bruitée
![alt text](output/noisy_image.png)

## Rotation de 90°
Le point où j’ai eu un peu de mal est de remplacer l’ancienne image par la nouvelle et de gérer correctement les dimensions et coordonnées lors de la rotation sans écraser les pixels en cours de route.

![alt text](output/rotation.png)

## RGB split
Au niveau du décalage horizontal des canaux, sortir des limites de l’image faisait planter le programme. J’ai dû utiliser `std::min` et `std::max` pour borner les coordonnées et empêcher le dépassement.

![alt text](output/rgb_split.png)

## Luminosité
![alt text](output/brightness.jpg)

## Disque
Je suis parti de l’inéquation `(x - a)² + (y - b)² < R²` pour tester la position de chaque pixel par rapport au centre.

![alt text](output/disk.png)

## Cercle
![alt text](output/circle.png)

## Animation
Le point sur lequel j’ai bloqué est que je n’avais pas pensé à faire une boucle extérieure pour itérer l’opération frame par frame, ce qui m’a fait placer la sauvegarde dans les boucles de pixels. J’ai aussi dû faire attention au nommage des fichiers via `std::to_string`.

![alt text](output/animation_video.gif)

## Rosace
J’ai cherché comment passer de coordonnées polaires (angle et rayon) à des coordonnées cartésiennes (x et y), ce qui m’a permis d’utiliser `x = r × cos(θ) et y = r × sin(θ)` pour placer les centres des cercles et calculer la distance. J’ai aussi dû faire attention à ne pas effacer les cercles déjà tracés avec un else qui remet en noir, à répartir les angles sur 360° (60° pour 6 cercles), et à bien gérer les conversions `int` et `float` pour éviter les erreurs de compilation.

![alt text](output/rosace.png)

## Glitch
J’ai rencontré plusieurs difficultés pour cet effet, notamment dans la génération des coordonnées aléatoires et la gestion des limites de l’image, ce qui provoquait des dépassements de pixels et des erreurs lors de l’exécution du programme.

![alt text](output/glitch.png)