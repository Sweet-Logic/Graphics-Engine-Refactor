#include "SceneFileHandler.h"

#include "../../SceneManagement/SceneManager.h"
#include "../../Utils/LinkedLists/LinkedLists.h"

bool SceneFileHandler::WriteToFile(char* filePath)
{
    std::ofstream outfile (filePath);
    if(outfile.is_open())
    {

        SceneGraph graph = SceneManager::GetInstance().GetSceneGraph();
        SceneGraph::Node *curr = graph.GetHead();
        while(curr != nullptr)
        {
            //Tell the children to return their serialised data.
            curr->value;// value->Serialise();

            curr = curr->A;
        }


        outfile.close();
        return true;
    }
    return false;
}

void SceneFileHandler::ReadFromFile(char* filePath)
{

}