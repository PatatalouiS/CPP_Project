
/////    OLIVIE Maxime - M1 IGAI UPS     /////
(Les commentaires de conception sont à la fin de ce README)


1) COMPILATION :

Un Makefile est fourni, il ne fonctionnera que sur des systèmes UNIX et MACOS
car il y a utilisation de certaines fonctions UNIX (notemment pour détecter si la commande est "pipée").

il faudra une version récente de g++ ou clang car la stdlib est utilisée
dans sa version de 2017.

La compilation a été testée et se passe san aucune erreur sur :
- Debian 10 (Buster)
- MAC OSX 10.14 (Mojave)

Pour compiler, se placer dans le répertoire à la racine et simplement :

$ make

Il existe des règles 

$ make clean

ou

$ make veryclean

Si jamais elle vous sont utiles.
N'hésitez pas a me contacter si vous avez des erreurs de compilation imprévues

2 ) EXECUTION

Apres avoir compilé les sources faire :

$ ./ExprApp    // A peu pret comme un interpréteur python/Node

ou alors :

$ cat [fichier] | ./ExprApp     // avec un pipe sur stdin

3 ) CHOIX DE CONCEPTION : 

Les Lexer et Parser ont été encapsulés dans des classes simples.

Le Lexer a été écrit de manière assez fonctionnelle, c-a-d avec des lambdas + unordered_map et regex,
car ayant déja paratiqué l'écriture de Lexer avec ocamllex et boost::spirit, le style fonctionnel se prête trés bien
à cette tache et les normes C++ récentes apportent au language un caractère multi-paradigme qui lui est à mon avis trés profitable.

Vous constaterez d'ailleurs que je n'ai pas utilisé le paradigme objet "a fond". Par exemple les classes binaryOp et
UnaryOp sont les plus basses dans la hiérarchie de classe, j'ai préféré utiliser encore une fois des lambdas et des tableaux de fonctions
pour instancier les différentes opérations (voir les fichiers BinaryOp.hpp et BinaryOp.cpp par exemple) car je trouve çela plus concis en général.

Des exceptions sont jetées pour divers cas d'erreurs (SyntaxError, et LexerError). J'ai peut être oublié certains cas d'erreurs mais normalement,
les erreurs de type : parentheses hasardeuses, ID non défini, ou opérateur placé incorrectement sont gérées. Elle ne mettent pas fin au programme
mais annulent la commande courante et re-affiche le "prompt" de l'application.

Vous constaterez aussi que chaque fihier header .hpp n'a pas forcément un .cpp associé, souvent les classes définies ont des fonctions 
trés courtes et sont donc directement inlinées dans le header.

J'ai également utilisé les smart pointers, (souvent les shared_ptr) car j'ai besoin de partager l'ownership d'un token vers un tableau, une pile...

Pour l'impléméntation de la définition/utilisation de variales, le type optional a été utilisé pour symboliser le fait qu'un ID peut ne pas posséder de valeur
(aide notemment à la gestion des erreurs sur un ID non défini).

Seules les feuilles de l'abre d'héritages sont instanciables, toutes les autres classes sont abstraites, avec de nombreuses méthodes virtuelles pures

4 ) A AMELIORER

Avec un peu plus de temps, j'aurais améliorer le point faible de l'application, qui est à mon gout l'utilisation un peu trop fréquente
des static_cast pour le transtypage. Ces casts sont sécurisés à l'aide de méthodes booléennes virtuelles qui renseignent le "type" d'un token, 
mais impléménter un Design Pattern Visitor aurait permit de s'affranchir de tout ces casts et les déléguer à la machine, en interne.

Je me suis forcé a essayé d'utiliser un modele POO le plus possible, car c'est l'intitulé de l'UE, mais j'avoue que mélanger POO et Prog fonctionnelle
est plus agréable pour moi en général, d'autant plus que le langage le permet aisément.

J'essaierai d'implémenter ce Design Pattern (et également la représentation en AST) pour le rendu final.

N'hésitez pas a me contacter si vous désirez plus de précisions, ou pour tout problème d'exécution/compilation



