# Réalisation en C++ d'un jeu de snake en réseau

Ce projet de C++ s'inscrit dans le cadre du cours IN204 de deuxième année à l'ENSTA ParisTech.

Le jeu s'inspire du célèbre [slither.io](http://slither.io) dont il reprend les grandes lignes.

# Instructions d'installation pour Linux

Le programme est compatible Windows et Linux, le Makefile a été configuré pour prendre en compte les deux OS. Les instructions suivantes seront cependant détaillées pour Linux.

* Clonez tout d'abord le projet sur votre PC en utilisant la commande suivante :

```
git clone https://github.com/lmichelin/slither.cpp
cd slither.cpp
```

* Vous pouvez éditer le fichier `mixins/headers/parameters.h` pour ajuster les options que vous souhaitez modifier.

* Rendez-vous dans le répertoire racine du projet et exécutez la commande :
```
make
```

* Si une erreur vous dit que SFML n'est pas installé, il faut l'installer. Sous Linux la commande est la suivante :
```
sudo apt-get install libsfml-dev
```

* Une fois que le projet est compilé, lancez le serveur :
```
./build/server
```

* Lancez le client sur les PC de chaque joueur :
```
./build/client [hostname]
```

Si vous ne renseignez pas l'hôte du serveur, celui du fichier `parameters.h` sera utilisé par défaut.

* Pour éviter de recompiler le programme sur le PC des autres joueurs, vous pouvez copier le dossier `build` et exécuter les commandes ci-dessus pour lancer le jeu.
