import string
import random

SAVE_PATH = "test_file.txt"

def generate_string(n_sim=1000):

    letters = string.ascii_lowercase
    rand_string = ''.join(random.choice(letters) for _ in range(n_sim))

    return rand_string

def write2txt(string):

    with open(SAVE_PATH, "w") as file:
        file.write(string)

if __name__ == "__main__":

    write2txt(generate_string())

