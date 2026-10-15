# Système de gestion de bibliothèque personnelle

**Nom :** Antoine Juteau  
**Cours :** 420-5G4 — C++

## Compilation et exécution

Le projet utilise CMake et peut être compilé dans un Dev Container C++ de Visual Studio Code.

Pour compiler le projet depuis sa racine :

```bash
cmake -S . -B build
cmake --build build
```

Pour exécuter le programme avec les fichiers de données :

```bash
./build/bibliotheque --data-dir donnees
```

L'option `-d` peut également être utilisée à la place de `--data-dir`.

## Répertoire de données

Le répertoire `donnees` contient les fichiers suivants :

- `books.txt` : contient les informations sur les livres.
- `users.txt` : contient les informations sur les utilisateurs.
- `journal.txt` : conserve l'historique des activités avec la date et l'heure de chaque opération. Ce fichier est créé automatiquement.

## Fonctionnalités implémentées

### 1. Implémentation de la classe Book

J'ai complété le fichier `book.cpp` afin d'implémenter les méthodes nécessaires à la gestion des livres, notamment la création, la consultation et la modification de leurs informations, ainsi que leur conversion pour la sauvegarde et le chargement.

### 2. Détection des livres en double

Lorsqu'un utilisateur tente d'ajouter un livre, le programme vérifie si un livre possédant le même titre, le même auteur et le même ISBN existe déjà. Si c'est le cas, l'ajout est refusé et un message d'erreur est affiché.

### 3. Tri des livres

Les livres sont affichés en ordre alphabétique selon leur titre. Lorsque deux livres ont le même titre, ils sont départagés selon le nom de leur auteur. Ce tri s'applique à l'affichage de tous les livres ainsi qu'à celui des livres disponibles.

### 4. Journal d'activités

J'ai ajouté un journal d'activités persistant qui enregistre les opérations effectuées dans la bibliothèque, comme l'ajout et la suppression de livres, l'ajout d'utilisateurs, les emprunts, les retours et les sauvegardes.

Chaque activité est enregistrée dans `journal.txt` avec la date, l'heure et une description de l'opération. Les anciennes entrées sont conservées lorsque le programme est fermé et relancé.

### 5. Correction de la sauvegarde

J'ai corrigé le comportement de sauvegarde à la fermeture du programme. Lorsqu'aucun répertoire de données n'est spécifié, le programme évite maintenant de tenter une sauvegarde vers des chemins de fichiers inexistants.

## Question 1 — C++ : Lecture et séparation des données avec `std::istringstream`

Pour ce projet, j'ai utilisé `std::istringstream`, qui fait partie de la bibliothèque `<sstream>` de C++. Cette classe permet de transformer une chaîne de caractères en un flux de lecture, comme si les données provenaient d'un fichier ou d'une entrée utilisateur. Je l'ai utilisée dans la méthode `Book::fromFileFormat()` du fichier `book.cpp`, pour récupérer les informations d'un livre à partir d'une seule ligne de texte.

Voici la méthode Book::fromFileFormat() que j'ai implémentée :

```cpp
void Book::fromFileFormat(const string& line) {
    string disponibilite;
    istringstream stream(line);

    getline(stream, title, '|');
    getline(stream, author, '|');
    getline(stream, isbn, '|');
    getline(stream, disponibilite, '|');

    isAvailable = (disponibilite == "1");

    getline(stream, borrowerId);
}
```

J'ai combiné cette fonctionnalité avec `std::getline()`, qui permet de lire une partie du flux jusqu'à un délimiteur précis. Dans le projet, les informations des livres sont séparées par le caractère `|`. En utilisant ce caractère comme délimiteur, j'ai pu extraire un à la suite de l'autre le titre, l'auteur, l'ISBN la disponibilité et le id de la personne qui a emprunté le livre si il n'est pas disponible.

Par exemple, pour une ligne contenant Naruto|Masashi Kishimoto|123|0|U01, le programme peut récupérer chaque valeur individuellement et l'utiliser pour reconstruire les informations d'un objet Book. Dans cet exemple, la valeur 0 indique que le livre n'est pas disponible, tandis que U01 représente l'identifiant de l'utilisateur qui l'a emprunté. Cette méthode évite d'avoir à parcourir manuellement la chaîne de caractères pour trouver les séparateurs.

Cette approche est particulièrement utile pour notre système de bibliothèque, puisqu'elle facilite le chargement des livres à partir du fichier `books.txt`. Elle permet également de conserver un format de sauvegarde simple et lisible.

## Question 2 — Options de développement possibles

Pour une bibliothèque contenant des millions de livres, je choisirais d'utiliser **PostgreSQL**, un système de gestion de base de données relationnelle, à la place de conserver toutes les informations dans des fichiers texte comme `books.txt` et `users.txt`. Le fonctionnement actuel est correct pour une petite bibliothèque, mais avec des millions de livres, les recherches et les modifications pourraient devenir vraiment plus lentes. En effet, le programme doit actuellement charger les données des fichiers et effectuer certaines recherches en parcourant les livres en mémoire. Une base de données permettrait de mieux organiser les informations dans des tables, par exemple une table pour les livres, une pour les utilisateurs et une pour les emprunts.

Un gros avantage de PostgreSQL est la possibilité de créer des **index** sur certaines colonnes, comme l'ISBN, le titre ou l'auteur. Ces index permettraient d'accélérer les recherches sans devoir parcourir systématiquement tous les livres. PostgreSQL permet aussi d'effectuer des recherches, des tris et des modifications directement dans la base de données à l'aide du langage SQL. Il serait donc possible de récupérer seulement les livres correspondant à une recherche, plutôt que de charger toute la bibliothèque en mémoire.

Pour faire communiquer PostgreSQL avec l'application C++, j'utiliserais la bibliothèque **libpqxx**, qui permet d'exécuter des requêtes SQL à partir du code C++. Par exemple, lorsqu'un utilisateur recherche un livre par son ISBN, le programme pourrait envoyer une requête SQL à PostgreSQL, récupérer le résultat et l'afficher dans l'application. Les classes C++ existantes, comme `Book` et `Library`, pourraient être conservées, mais certaines de leurs méthodes devraient être adaptées pour fonctionner avec la base de données plutôt qu'avec les fichiers texte.

Cette solution permettrait donc de conserver C++ comme langage principal tout en utilisant PostgreSQL pour gérer efficacement une grande quantité de données. Elle faciliterait aussi l'évolution du projet si plusieurs utilisateurs devaient accéder à la bibliothèque en même temps.