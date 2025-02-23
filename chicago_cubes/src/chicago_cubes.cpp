float deg2rad(float degrees)
{
    float radians = 0.0f;

    float convert = M_PI / 180.0f;

    radians = degrees * convert;

    return radians;
}

v3 hsv2rgb(float h, float s, float v)
{
    v3 out = {};

    float chroma = s * v;
    float hprime = h / 60.0f;

    float xfactor = chroma * (1.0f - fabsf(fmodf(hprime, 2.0f) - 1.0f));

    float m = v - chroma;

    out.r += m;
    out.g += m;
    out.b += m;

    if(0.0f <= hprime && hprime <= 1.0f)
    {
        out.r += chroma;
        out.g += xfactor;
    }
    else if(hprime <= 2.0f)
    {
        out.r += xfactor;
        out.g += chroma;
    }
    else if(hprime <= 3.0f)
    {
        out.g += chroma;
        out.b += xfactor;
    }
    else if(hprime <= 4.0f)
    {
        out.g += xfactor;
        out.b += chroma;
    }
    else if(hprime <= 5.0f)
    {
        out.r += xfactor;
        out.b += chroma;
    }
    else if(hprime <= 6.0f)
    {
        out.r += chroma;
        out.b += xfactor;
    }

    return out;
}

void sdl_process_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            global_running = false;
        }
        else if(event.type == SDL_WINDOWEVENT &&
                event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            global_running = false;
        }
		else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			bool was_down = event.key.state == SDL_RELEASED || event.key.repeat;
			bool is_down = event.key.state == SDL_PRESSED;
			if(is_down != was_down)
			{
				switch(event.key.keysym.sym)
				{
					case '0':
					{
						mode = 0;
					} break;
					case '1':
					{
						mode = 1;
					} break;
					case '2':
					{
						mode = 2;
					} break;
					case '3':
					{
						mode = 3;
					} break;
				}
			}
		}
    }
}

void generate_offsets()
{
    for(int i = 0; i < MAX_OFFSET; i++)
    {
        offset[i] = (float)(rand() % 3600) / 10.0f;
        // offset[i] = (float)(rand() % 10) / 100.0f;
    }
}

void draw_cube(float x, float y, float z, float size)
{
    float half = size / 2.0f;

    float depth = 1.0f / 9.0f;

    float h = ((z + 1.15) * 1800.0f) + 180.0f;
    float s = 0.2f;
    float v = 0.8f;

    v3 color = hsv2rgb(h, s, v);

    glBegin(GL_TRIANGLES);

    // Bottom
    glColor3f(color.r / 2.0f, color.g / 2.0f, color.b / 2.0f);
    // Near
    glVertex3f(x + half, y - half, z);
    glVertex3f(x - half, y - half, z);
    glVertex3f(x - half, y - half, z - depth);
    // Far
    glVertex3f(x - half, y - half, z - depth);
    glVertex3f(x + half, y - half, z - depth);
    glVertex3f(x + half, y - half, z);

    // Left
    glColor3f(color.r / 1.75f, color.g / 1.75f, color.b / 1.75f);
    // Near
    glVertex3f(x - half, y - half, z);
    glVertex3f(x - half, y + half, z);
    glVertex3f(x - half, y + half, z - depth);
    // Far
    glVertex3f(x - half, y + half, z - depth);
    glVertex3f(x - half, y - half, z - depth);
    glVertex3f(x - half, y - half, z);

    // Right
    glColor3f(color.r / 1.5f, color.g / 1.5f, color.b / 1.5f);
    // Near
    glVertex3f(x + half, y + half, z);
    glVertex3f(x + half, y - half, z);
    glVertex3f(x + half, y - half, z - depth);
    // Far
    glVertex3f(x + half, y - half, z - depth);
    glVertex3f(x + half, y + half, z - depth);
    glVertex3f(x + half, y + half, z);

    // Top
    glColor3f(color.r / 1.25f, color.g / 1.25f, color.b / 1.25f);
    // Near
    glVertex3f(x - half, y + half, z);
    glVertex3f(x + half, y + half, z);
    glVertex3f(x + half, y + half, z - depth);
    // Far
    glVertex3f(x + half, y + half, z - depth);
    glVertex3f(x - half, y + half, z - depth);
    glVertex3f(x - half, y + half, z);

    // Front
    glColor3f(color.r, color.g, color.b);
    // Top-left
    glVertex3f(x + half, y + half, z);
    glVertex3f(x - half, y + half, z);
    glVertex3f(x - half, y - half, z);
    // Bottom-right
    glVertex3f(x - half, y - half, z);
    glVertex3f(x + half, y - half, z);
    glVertex3f(x + half, y + half, z);

    glEnd();
}

void draw_cubes_move(float angle)
{
    float size = PX_HEIGHT / 9;

    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            float x = (float)i * size + size / 2.0f;
            float y = (float)j * size + size / 2.0f;

            int index = 9 * i + j;

            float z = SDL_sin(deg2rad(angle + offset[index])) / 10.0f - 1.15f;

            x -= PX_WIDTH / 2.0f;
            y -= PX_HEIGHT / 2.0f;

            draw_cube(x, y, z, size);
        }
    }
}

void draw_prism(float x, float y, float z, float size)
{
    float half = size / 2.0f;

    float depth = 1.0f;// / 9.0f;

    float h = ((z + 1.15) * 1800.0f) + 180.0f;
    float s = 0.2f;
    float v = 0.8f;

    v3 color = hsv2rgb(h, s, v);
    // v3 color = { 0.6f, 0.3f, 0.4f };

    // printf("%f\n", h);

    glBegin(GL_TRIANGLES);

    // Bottom
    glColor3f(color.r / 2.0f, color.g / 2.0f, color.b / 2.0f);
    // Near
    glVertex3f(x + half, y - half, z);
    glVertex3f(x - half, y - half, z);
    glVertex3f(x - half, y - half, z - depth);
    // Far
    glVertex3f(x - half, y - half, z - depth);
    glVertex3f(x + half, y - half, z - depth);
    glVertex3f(x + half, y - half, z);

    // Left
    glColor3f(color.r / 1.75f, color.g / 1.75f, color.b / 1.75f);
    // Near
    glVertex3f(x - half, y - half, z);
    glVertex3f(x - half, y + half, z);
    glVertex3f(x - half, y + half, z - depth);
    // Far
    glVertex3f(x - half, y + half, z - depth);
    glVertex3f(x - half, y - half, z - depth);
    glVertex3f(x - half, y - half, z);

    // Right
    glColor3f(color.r / 1.5f, color.g / 1.5f, color.b / 1.5f);
    // Near
    glVertex3f(x + half, y + half, z);
    glVertex3f(x + half, y - half, z);
    glVertex3f(x + half, y - half, z - depth);
    // Far
    glVertex3f(x + half, y - half, z - depth);
    glVertex3f(x + half, y + half, z - depth);
    glVertex3f(x + half, y + half, z);

    // Top
    glColor3f(color.r / 1.25f, color.g / 1.25f, color.b / 1.25f);
    // Near
    glVertex3f(x - half, y + half, z);
    glVertex3f(x + half, y + half, z);
    glVertex3f(x + half, y + half, z - depth);
    // Far
    glVertex3f(x + half, y + half, z - depth);
    glVertex3f(x - half, y + half, z - depth);
    glVertex3f(x - half, y + half, z);

    // Front
    glColor3f(color.r, color.g, color.b);
    // Top-left
    glVertex3f(x + half, y + half, z);
    glVertex3f(x - half, y + half, z);
    glVertex3f(x - half, y - half, z);
    // Bottom-right
    glVertex3f(x - half, y - half, z);
    glVertex3f(x + half, y - half, z);
    glVertex3f(x + half, y + half, z);

    glEnd();
}

void draw_cubes_stretch(float angle)
{
    float size = PX_HEIGHT / 9;

    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            float x = (float)i * size + size / 2.0f;
            float y = (float)j * size + size / 2.0f;

            int index = 9 * i + j;

            float z = SDL_sin(deg2rad(angle + offset[index])) / 10.0f - 1.15f;

            x -= PX_WIDTH / 2.0f;
            y -= PX_HEIGHT / 2.0f;

            draw_prism(x, y, z, size);
        }
    }
}

void draw_square(float x, float y, float z, float size)
{
    float half = size / 2.0f;

    v3 color = { 0.6f, 0.3f, 0.4f };

    glBegin(GL_TRIANGLES);

    glColor3f(color.r, color.g, color.b);

    glVertex3f(x + half, y + half, z);
    glVertex3f(x - half, y + half, z);
    glVertex3f(x - half, y - half, z);

    glColor3f(color.b, color.g, color.r);

    glVertex3f(x - half, y - half, z);
    glVertex3f(x + half, y - half, z);
    glVertex3f(x + half, y + half, z);

    glEnd();
}

void draw_squares()
{
	static int square_timer = 15;
	static float z_values[16 * 9] = {};

	if(square_timer > 5)
	{
		square_timer = 0;
		for(int i = 0; i < 16; i++)
		{
			for(int j = 0; j < 9; j++)
			{
				z_values[i * 16 + j] = (float)(rand() % 10) / 100.0f - 1.15f;
			}
		}
	}
	++square_timer;

	float size = PX_HEIGHT / 9;

	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			float x = (float)i * size + size / 2.0f;
			float y = (float)j * size + size / 2.0f;

			float z = z_values[i * 16 + j];

			x -= PX_WIDTH / 2.0f;
			y -= PX_HEIGHT / 2.0f;

			draw_square(x, y, z, size);
		}
	}
}

void draw_diamond(float x, float y, float z, float size)
{
    float half = size;

    float h = (float)(rand() % 360);
    float s = 0.33f;
    float v = 0.66f;

    v3 color = hsv2rgb(h, s, v);

    glBegin(GL_TRIANGLES);

    glColor3f(color.r, color.g, color.b);

    glVertex3f(x - half, y, z);
    glVertex3f(x, y - half, z);
    glVertex3f(x + half, y, z);

    glVertex3f(x + half, y, z);
    glVertex3f(x, y + half, z);
    glVertex3f(x - half, y, z);

    glEnd();
}

void draw_diamond_mats()
{
    float size = PX_HEIGHT / 9;

    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            float x = (float)i * size + size / 2.0f;
            float y = (float)j * size + size / 2.0f;

            float z = -1.5f;

            x -= PX_WIDTH / 2.0f;
            y -= PX_HEIGHT / 2.0f;

            draw_diamond(x, y, z, size);
        }
    }
}

void draw_diamond_shuffle(float angle)
{
    float size = PX_HEIGHT / 9;

    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            float x = (float)i * size + size / 2.0f;
            float y = (float)j * size + size / 2.0f;

            float z = (float)(rand() % 10) / 100.0f - 1.15f;

            x -= PX_WIDTH / 2.0f;
            y -= PX_HEIGHT / 2.0f;

            x *= SDL_cos(angle);
            y *= SDL_sin(angle);

            draw_diamond(x, y, z, size);
        }
    }
}
