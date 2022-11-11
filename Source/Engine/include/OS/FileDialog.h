extern "C"
{
    #include <nfd.h>
}
#include <string>

namespace Engine::OS
{
    class FileDialog
    {
    public:
        static std::string OpenFile(const std::string& filters = "None", const std::string& defpath = "None")
        {
            const nfdchar_t* nfd_filters = filters.empty() || "None" ? nullptr : filters.c_str();
            const nfdchar_t* nfd_defpath = defpath.empty() || "None" ? nullptr : defpath.c_str();

            nfdchar_t* outpath = nullptr;
            switch (NFD_OpenDialog(nfd_filters, nfd_defpath, &outpath))
            {
            case NFD_OKAY:
                return std::string(outpath);
            case NFD_CANCEL:
                break;
            default:
                // TODO: ADD TO LOG
                // printf ("Error: %s\n", NFD_GetError ())
                break;
            }

            return std::string();
        }

        static std::string SaveFile(const std::string& filters = "None", const std::string& defpath = "None")
        {
            const nfdchar_t* nfd_filters = filters.empty() || "None" ? nullptr : filters.c_str();
            const nfdchar_t* nfd_defpath = defpath.empty() || "None" ? nullptr : defpath.c_str();

            nfdchar_t* savepath = nullptr;
            switch (NFD_SaveDialog(nfd_filters, nfd_defpath, &savepath))
            {
            case NFD_OKAY:
                return std::string(savepath);
            case NFD_CANCEL:
                break;
            default:
                // TODO: ADD TO LOG
                // printf ("Error: %s\n", NFD_GetError ())
                break;
            }

            return std::string();
        }
        
    };
}