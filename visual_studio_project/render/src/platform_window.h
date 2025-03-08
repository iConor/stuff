#pragma once


namespace platform
{
    class window
    {
    public:
        static window* load();

        virtual void show() = 0;
        virtual bool msgs() = 0;
    private:
        virtual void create() = 0;
        virtual void destroy() = 0;
    };

}
