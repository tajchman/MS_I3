# MS_I3
### Cours MS-I3 : Programmation hybride et multi-coeurs  [2024/2025]

## Organisation

| Horaire : | Cours et TD/TP le vendredi matin  [Planning détaillé] |
| Enseignant : | Marc Tajchman, CEA, DEN/DM2S/STMF/LMES |

Prérequis
Il est conseillé aux étudiants qui souhaitent suivre ce cours, d'avoir déjà utilisé des machines de calcul sous linux, les outils standards (shell, éditeurs, etc) et les outils de progammation (tels que compilateurs, cmake, make, débogeurs, etc) disponibles dans cette plateforme.
Les exemples et exercices ont été testés sur le cluster Cholesky, mais devraient fonctionner sur d'autres environnements (linux, macOs ou windows sur machine personnelle) à condition d'installer des outils adéquats. Ne pas hésiter à poser des questions en cas de soucis.

La connaissance d'un langage de programmation utilisé dans le domaine scientifique, de préférence C++ (les notions de C++ nécessaires sont de niveau basique), est indispensable pour effectuer les travaux pratiques demandés.

Dans la seconde partie du cours, on utilisera des fonctionnalités (un peu) plus avancées de C++ (fonctions lambda, templates), une séance spécifique de ce cours leur sera consacrée. A nouveau, en cas de difficultés, ne pas hésiter à poser des questions.

Enfin, on supposera que les étudiants ont des notions en programmation parallèle avec MPI, obtenues par exemple en suivant Cours MS01 - Calcul Scientifique Parallèle.

Programme du cours
Le programme ci-dessous est indicatif, il est susceptible de légères adaptations. On ajoutera au fur et à mesure de l'avancement du cours, des références sur les supports de cours et les fichiers sources des exercices et TP.
Quelques conseils et remarques concernant les TPs et exemples

Rappels sur les architectures des machines et différents types de programmation parallèle (1/2 séance)
Support de cours : Introduction et Rappels d'architecture des ordinateurs

Optimisation de la programmation séquentielle (1/2 séance)

Support de cours : Optimisation de la programmation séquentielle
Mémoire cache des machines.
Notions de localités spatiale et temporelle.
Utiliser les possibilités du processeur.
Influence sur l'efficacité des algorithmes.
Exemples. (format tar + gzip, format zip)
Programmation multi-threads (2 séances).

Séance 1: notions de base (support de cours : Programmation multi-threads (partie 1))
Différents outils disponibles.
Variables partagées ou non entre threads.
Exemples avec OpenMP, TBB, std::threads (format tar + gzip, format zip)
Séance 2: techniques de programmation multi-threads
Différentes techniques de programmation avec OpenMP : grain fin, grain grossier, programmation par tâches
(support de cours : Programmation multi-threads (partie 2)).
Exemples (format tar + gzip, format zip)
TP 1 : Enoncé et code source à modifier/compléter: format tar + gzip, format zip
Programmation hybride multi-noeuds - multi-coeurs (2 séances).

Intérêt de ce type d'approche.
Comparaison de différentes techniques MPI-OpenMP.
Exemples
Programmation des GPU (Graphics Processing Unit) (5 séances).

Les outils de base: Cuda, OpenCL (fonctionnalités, avantages/inconvénients).
Quelques notions de performance dans la programmation avec Cuda des GPUs: illustration sur des exemples
Environnement de programmation autour de Cuda: outils et librairies disponibles
Exemple : la librairie Thrust
Notion de foncteur en C++ (ou objet-fonction)
Un outil visant la portabilité sur plusieurs modèles de programmation: Kokkos
Un outil visant la portabilité sur plusieurs modèles de programmation: Sycl
Programmation Multi-GPU

Plusieurs GPU associés au même CPU (combinaison Cuda + OpenMP):
Plusieurs GPU associés chacun à un CPU. (combinaison Cuda + MPI):