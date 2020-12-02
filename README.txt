
/////    OLIVIE Maxime - M1 IGAI UPS  -   //////
/////    README TP CPP Phase 2           //////

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

3 ) MODIFICATIONS APPORTEES A LA PHASE 1 : 

Une des principales gênes que j'avais avec ma précédente conception était l'utilisation trop fréquente des casts statiques sur mes pointeurs.
C'est en jettant un coup d'oeil aux éléments de correction donnés que je me suis rendu compte que la signature de ma fonctions virtuelles eval() était
Bien trop précise. En effet le type de eval(), précédemment, était (const double& a = 0, const double& = 0) -> double. Ceci a été changé
Par (TokenStack& stack) -> double, ce qui fait respirer le code et en simplifie grandement l'évaluation, déléguant la gestion de la pile aux tokens et non plus a la classe Expr.
Cela m'a permit donc de remplacer les arguments par défaut de l'ancienne signature, les arguments par défauts étant fortement déconseillés dans une fonction virtuelle pour cause
de comportements curieux.

Mis a part ceci, un peu de refactoring, et de simplification de la hiérarchie de classe, le code est resté identique à celui de la phase 1 

4 ) COMMENTAIRES PHASE 2

J'ai trouvé cette phase bien plus facile que la première, surtout car elle est plus axée sur l'aspect fonctionnel du C++.
J'ai directement commencé par considérer que toutes les fonctions étaient variadiques, les fonctions unaires et n-aires étants une sorte de "spécialisation".
Une seule classe Func a donc été rajoutée. Une hashmap est utilisée pour accéder aux fonctions associées par leur nom (string). La valeur associée à la clé
De la hashmap est une structure "wrapper" qui contient tout ce que nous avons besoin de savoir sur la fonction :

- son nombre d'arguments,
- un booléen indiquant si elle est variadique,
- Un handler d'exécution de cette fonction, de type (const Args&) -> double (Args étant un tableau d'arguments pour les fonctions)

Il suffit alors, dans la méthode virtuelle eval() de la classe Func, de dépiler autant d'arguments dans la pile qu'il y a d'arguments déclarés dans la fonction, puis d'exécuter le handler associé avec les arguments dépilés, mis dans un container.

La détection du nombre d'arguments est faite par un algorithme qui compte le nombre de ',' présents jusqu'à la parenthèse fermante de l'appel de fonction,
En prenant soin de ne compter que les ',' qui sont au même niveau de parenthésage que les parenthèses de l'appel de fonction, ce qui permet d'évaluer des expressions 
complexes et imbriquées comme :

polynome(pow(1, 2) * 2, 2 - 1, -1*(-1), -(-1), cos(0) * cos(0) + 1 * lerp(0,1,1)) * -(-(-(-(-(-(-1))))))
(  résultat : -7 )

Cette fonction renvoie le nombre d'arguments détectés dans un appel de fonction, ou renvoie null_opt si la détection est un échec
(Erreur de syntaxe par exemple : "lerp(1,2,"   ).

Enfin, une fois le nom de la fonction détecté et son nombre d'arguments calculé, on peux regarder si elle est valide. C'est à dire si une fonction de ce nom existe 
Dans notre hashmap, avec le même nombre d'arguments si elle n'est pas variadique).

toutes les fonctions demandées ont donc pu être implémentées.

5) A AMELIORER

A mon sens, Les défauts de ce code ne manquent pas. Il est parfois trop verbeux Mais le temps m'a manqué pour le peaufiner très précisément.
J'espère avoir le temps pour le rendu final de TP pour le rendre tel que j'aimerai qu'il soit.

Egalement, je trouve la gestion des erreurs satisfaisante, mais elle peut encore être améliorée avec un peu de temps en plus. Par exemple j'ai rajouté le cas :

Expr >>> lerp(1, 2)
Résultat : Syntax Error : Function : "lerp" with 2 arguments is not defined







