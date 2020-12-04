
/////    OLIVIE Maxime - M1 IGAI UPS  -   //////
/////    README TP CPP Phase 3           //////

(Les commentaires de conception sont à la fin de ce README,
Au début ne figure qu'un rappel des instructions de compilation
Et d'exécution)


1) COMPILATION :

Un Makefile est fourni, il ne fonctionnera que sur des systèmes UNIX et MACOS
car il y a utilisation de certaines fonctions UNIX (notamment pour détecter si la commande est "pipée").

il faudra une version récente de g++ ou clang car la stdlib est utilisée
dans sa version de 2017. (C++17)

La compilation a été testée et se passe sans aucune erreur sur :
- Debian 10 (Buster)
- MAC OSX 10.14 (Mojave)

Pour compiler, se placer dans le répertoire à la racine et simplement :

$ make

Il existe des règles 

$ make clean

ou

$ make veryclean

Si jamais elles vous sont utiles.
N'hésitez pas a me contacter si vous avez des erreurs de compilation imprévues

2 ) EXECUTION

Apres avoir compilé les sources faire :

$ ./ExprApp    // A peu prêt comme un interpréteur python/Node

ou alors :

$ cat [fichier] | ./ExprApp     // avec un pipe sur stdin

3 ) MODIFICATIONS APPORTEES A LA PHASE 2 : 

Un peu de refactoring général du code a été fait dans un but de simplification. Mmis à part ceci, le code que j'ai présenté en phase 2, mis à part les ajouts de phase 3, reste inchangé.

4 ) COMMENTAIRES PHASE 2

J'ai trouvé cette phase assez simple, surtout car je suis un grand fan de l'aspect fonctionnel du C++, que l'on doit ici utiliser à foison.
J'ai considéré maintenant que une évaluation d'une instruction peux avoir 2 types de retour : un double, ou une fonction.
La classe "setoperator" a été créee, elle représente l'opérateur '=', et cette classe a pour but de réaliser les affectations
de variables , que ce soit des réels ou des fonctions.

L'essentiel du code de cette phase ce trouve donc dans la classe 'setoperator'. 

Pour la curryfication, je créer une nouvelle fonction et l'ajoute à la "table des fonctions" de l'application. cette fonction est définie par une lambda, qui prend en paramètre les arguments restants à donner pour l'évaluation. La liste complete des arguments est recrée en utilisant le liste des premiers arguments en capure de la lambda.

On a le comportement voulu cad :

Expr>>>   myfunc = lerp(0.7)
	Function : myfunc
	Type : ( val * val ) -> val
Expr>>>   myfunc2 = myfunc(3)
	Function : myfunc2
	Type : ( val ) -> val
Expr>>>   myfunc2(4)
	3.7

Pour les placeholder, c'est un peu de la même manière que ceci est réalisé, à la différence que l'on va capturer également les placeholders donnés.
C'est a l'intérieur de la lambda que l'on va s'occuper de "mapper" chaque argument au bon endroit dans le tableau d'arguments en fonctions des placeholder.

Nous avons donc les comportements suivants :

Expr >>>  myfunc = lerp(_1, 3, _2)
	Function : myfunc
	Type : ( val * val ) -> val
Expr >>>  myfunc(0.7, 4)
	3.7

Il est alors possible même d'inverser l'ordre des arguments avec les placholders :

Expr >>>  myfunc = lerp(_3, _2, _1)
    Function : myfunc
    Type : ( val * val * val ) -> val
Expr >>>  myfunc(4, 3, 0.7)
    3.7

5) A AMELIORER

A mon sens, Les défauts de ce code ne manquent pas. Il est parfois trop verbeux Mais le temps m'a manqué pour le peaufiner très précisément.

Egalement, je trouve la gestion des erreurs satisfaisante, mais elle peut encore être améliorée avec un peu de temps en plus.






