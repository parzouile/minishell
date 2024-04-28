#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> // Pour les constantes de contrôle des fichiers

// Fonction pour effectuer les redirections
void effectuerRedirections(int fichier_sortie, int fichier_erreur) {
    // Dupliquer les descripteurs de fichier actuels
    int sauvegarde_stdout = dup(STDOUT_FILENO);
    int sauvegarde_stderr = dup(STDERR_FILENO);

    // Rediriger la sortie standard et la sortie d'erreur vers les nouveaux fichiers
    if (dup2(fichier_sortie, STDOUT_FILENO) == -1 || dup2(fichier_erreur, STDERR_FILENO) == -1) {
        perror("Erreur lors de la redirection de la sortie standard ou d'erreur");
        exit(EXIT_FAILURE);
    }
    
    // Utiliser les nouveaux descripteurs de fichier pour les opérations d'écriture

    // Exemple d'utilisation : printf("Hello, redirection!\n");

    // Rétablir les redirections initiales
    dup2(sauvegarde_stdout, STDOUT_FILENO);
    dup2(sauvegarde_stderr, STDERR_FILENO);

    // Fermer les descripteurs de fichier dupliqués
    close(sauvegarde_stdout);
    close(sauvegarde_stderr);
}

int main() {
    // Ouvrir ou créer les fichiers de sortie
    int fichier_sortie = open("sortie.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Fermer les fichiers
    close(fichier_sortie);
    close(fichier_sortie);

    return 0;
}
