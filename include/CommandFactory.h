#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "Commands/CommandEcho.h"
#include "Commands/CommandPrompt.h"
#include "Commands/CommandTime.h"
#include "Commands/CommandDate.h"
#include "Commands/CommandTouch.h"
#include "Commands/CommandTruncate.h"
#include "Commands/CommandRm.h"
#include "Commands/CommandWc.h"
#include "Commands/CommandTr.h"
#include "Commands/CommandHead.h"
#include "Commands/CommandBatch.h"

class CommandFactory {
    //creates a class Command
public:
    unique_ptr<Command> createCommand(const string& name) const;
};

#endif //COMMANDFACTORY_H
