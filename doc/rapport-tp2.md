---
title: "Compte-rendu TP2"
subtitle: "Traitement d'images"
author: [Alexis Da Costa, Julien Save]
date: "2021-09-12"
keywords: [Markdown, Example]
abstract : Ce court document est destiné à faire un compte-rendu des réalisations effectués lors de ce TP2. L’objectif du TP est d’implémenter un d ́etecteur d’objets circulaires par une m ́ethode cumulative de type Hough.
numbersections : true
---

<div style="page-break-after: always; visibility: hidden">\pagebreak</div>

# Exercice 1 : La transformée de Hough pour les cercles
Soit une paramétrisation de type $(r, c, rad)$ pour définir un cercle de rayon $rad$ pixels dans l’image, dont le centre est situé sur la ligne $r$ et la colonne $c$. Comme nous sommes obligés de considérer un ensemble discret de paramètres, on retient toutes les positions $r \in [r_{min}, r_{max}]$ avec un pas de discrétisation de $\delta r$, et ainsi de suite pour $c \in [c_{min}, c_{max}]$ avec un pas de discrétisation de $\delta c$ et pour $rad ∈ [rad_{min}, rad_{max}]$ avec un pas de discrétisation de $\delta rad$.

1. Pour l'image *four.png* fournie, de taille $100 \times 100$, considérons que $r_{min} = 1, r_{max} = 100, \delta r = 2$. Combien de valeurs discrètes aura-t-on pour la coordonnée $r$ des cercles ?

*Dans ce premier cas, nous aurons **50 valeurs discrètes**.*