/*
I BogDan Vatra < bog_dan_ro@yahoo.com >, the copyright holder of this work,
hereby release it into the public domain. This applies worldwide.

In case this is not legally possible, I grant any entity the right to use
this work for any purpose, without any conditions, unless such conditions
are required by law.
*/

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
