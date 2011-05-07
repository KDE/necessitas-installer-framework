#ifndef REGISTERQTCREATORSOURCEMAPPINGOPERATION_H
#define REGISTERQTCREATORSOURCEMAPPINGOPERATION_H
#include <KDUpdater/UpdateOperation>
namespace QInstaller {

class RegisterQtCreatorSourceMappingOperation : public KDUpdater::UpdateOperation
{
public:
    RegisterQtCreatorSourceMappingOperation();
    void backup();
    bool performOperation();
    bool undoOperation();
    bool testOperation();
    KDUpdater::UpdateOperation* clone() const;
};

}; // namespace
#endif // REGISTERQTCREATORSOURCEMAPPINGOPERATION_H
