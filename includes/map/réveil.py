import time
from playsound import playsound

# Fonction pour jouer le son de l'alarme
def jouer_alarme():
    # Utilise playsound pour jouer un son d'alarme
    # Modifiez le chemin du fichier sonore si nécessaire
    playsound("midu.wav")

# Convertit une durée en secondes
def convertir_en_secondes(heures, minutes, secondes):
    return heures * 3600 + minutes * 60 + secondes

# Obtient l'heure actuelle
maintenant = time.localtime()

# Obtient l'heure de l'alarme
heure_alarme = time.localtime(time.time() + convertir_en_secondes(0, 0, 10))

# Attend jusqu'à l'heure de l'alarme
time.sleep(convertir_en_secondes(0, 0, 10))

# Joue l'alarme
jouer_alarme()
