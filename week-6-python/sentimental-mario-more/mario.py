from cs50 import get_int


def generate(height):
    for i in range(1, (height + 1)):
        spaces = ' ' * (height - i)
        blocks = '#' * i
        print(f'{spaces}{blocks}  {blocks}')


def get_height():
    while True:
        try:
            height = get_int("Height: ")
            if (height > 0 and height < 9):
                break
        except ValueError:
            None

    return height


if __name__ == "__main__":
    height = get_height()
    generate(height)