Calcul les derivées horizontal et vertical
Calculer les racines des derivées 
Calculer le seuil (pixel de contour ou de fin) 
==> image en noir et blanc sauf pixel des cercles (en 255) = image de contour 
Equation de cercle : (x−xc)^2+(y−yc)^2=r²
On prend cette image de contour, on construit la matrice 3D 
Avec autant de case que de solution pour Xcmax, Ycmax et rmax 
Xcmax = taille de l'image, ycmax = taille de l'image  et rmax = diag de l'image 
Pour une image de 800*600 ==> xcmax = 800, ycmax = 600 et rmax = 1000
Matrice 3D de : 1000*800*600*4 = 1920000000 (2Go)

On la construit avec les cases à 0
On se balade dans l'image de contour et lorsqu'on tombe sur un pixel à 255 (x1,y1): 
	- On calcul avec chaque pixel le cercle qui passe par le point x1,y1 et on ignore les petits ==> applicable à tous les pixel de contour 
Dedans nous aurons le bon cercle grace à l'incrementation de 1.0/r dans la matrice 3D ==> 1.0/r donne de l'importance au rayon si le cercle est full visible on trouve 2pi dans la case 
Le bon aura enormement de vote dans la matrice 3D 


Astuce pour les images de grandes tailles : 

On cherche une droite perpendiculaire au pixel de contour ==> gradiant du point (filtre de sobel)  
On reprends les derivées et la direction est données par le gradiant et nous regardons uniquement dans les pixels qui sont dans la direction donnée + quelques pixels autour ==> economie de temps mais pas de mémoire 

Image 1000 * 1000
On divise l'image par 2 
Et encore et encore 
On fait le traitement sur la petite image
Les coordonnées sont les coordonnées de la petite image fois le nbr de divisions 

Et on revient dans l'autre sens pour trouver les petits en faisant une restriction de [rmin, 2rmn] pour trouver les cercles