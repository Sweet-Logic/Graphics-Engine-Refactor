#ifndef _SCENE_FILE_HANDLER_H_
#define _SCENE_FILE_HANDLER_H_
#include "FileHandler.h"

struct SceneFileHandler : public FileHandler<SceneFileHandler>
{
    bool WriteToFile(char* filePath) override;
    void ReadFromFile(char* filePath) override;
};

#endif //!_SCENE_FILE_HANDLER_H_