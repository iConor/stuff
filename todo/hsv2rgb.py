def hsv2rgb(h, s, v):

    c = s * v
    hp = h / 60
    x = c * (1 - abs(hp % 2 - 1))

    if hp < 0:
        r, g, b = 0, 0, 0
    elif hp < 1:
        r, g, b = c, x, 0
    elif hp < 2:
        r, g, b = x, c, 0
    elif hp < 3:
        r, g, b = 0, c, x
    elif hp < 4:
        r, g, b = 0, x, c
    elif hp < 5:
        r, g, b = x, 0, c
    elif hp < 6:
        r, g, b = c, 0, x
    else:
        r, g, b = 0, 0, 0

    m = v - c

    r, g, b = r+m, g+m, b+m

    return r, g, b


def hsl2rgb(h, s, l):

    c = (1 - abs(2*l - 1)) * s
    hp = h / 60
    x = c * (1 - abs(hp % 2 - 1))

    if hp < 0:
        r, g, b = 0, 0, 0
    elif hp < 1:
        r, g, b = c, x, 0
    elif hp < 2:
        r, g, b = x, c, 0
    elif hp < 3:
        r, g, b = 0, c, x
    elif hp < 4:
        r, g, b = 0, x, c
    elif hp < 5:
        r, g, b = x, 0, c
    elif hp < 6:
        r, g, b = c, 0, x
    else:
        r, g, b = 0, 0, 0

    m = l - (c / 2)

    r, g, b = r+m, g+m, b+m

    return r, g, b
