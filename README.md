# Hough Cercle Detection

Voici un petit README.md afin d'expliquer comment compiler et exécuter notre traitement de detection de cercle par la transformé de Hough. 

## Pour compiler : 

```cmake
mkdir build 
cd build  
cmake ../  
make        
```

## Pour exécuter : 

```cmake
./bin/TP2 ../src/images/image_name weight_value radmin_value radmax_value
```

Veuillez rentrer en paramètre : 

- ```image_name``` : le nom de l'image à traiter
- ```weight_value``` : la valeur dans l'accumultateur à partir duquel on souhaite afficher un cercle 
- ```radmin_value``` : le rayon minimum
- ```radmax_value``` : le rayon maximum

L'ensemble des images sont dans le répertoire ```src/images```. 

Pour l'image ```four.png```, voici les paramètres à rentrer :

``````
./bin/TP2 ../src/images/four.png 4.5 4 86
``````

Pour l'image ```coins2.jpg```, voici les paramètres à rentrer :

``````
./bin/TP2 ../src/images/coins2.jpg 3.5 10 90
``````

