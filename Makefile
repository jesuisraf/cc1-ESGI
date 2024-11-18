# Définir le compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -g

# Nom de l'exécutable final
TARGET = program

# Fichiers source
SRC = main.c student.c sql.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Fichiers d'en-tête (ajout pour s'assurer que les dépendances sont prises en compte)
HEADERS = student.h sql.h

# Règle pour générer les dépendances automatiquement
-include $(OBJ:.o=.d)

# Règle pour construire l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Règle pour compiler les fichiers .c en .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour générer les fichiers de dépendances .d
%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

# Règle pour nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ) $(TARGET)

# Règle pour tout nettoyer (y compris l'exécutable)
fclean: clean
	rm -f $(TARGET)

# Règle pour recompiler tout depuis zéro
re: fclean $(TARGET)

# Règle par défaut (compiler le programme)
all: $(TARGET)
