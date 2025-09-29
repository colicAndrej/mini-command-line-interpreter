#include "CommandFactory.h"

unique_ptr<Command> CommandFactory::createCommand(const string& name) const {
    if (name == "echo")
        return make_unique<CommandEcho>();
    if (name == "prompt")
        return make_unique<Prompt>();
    if (name == "time")
        return make_unique<Time>();
    if (name == "date")
        return make_unique<CommandDate>();
    if (name == "touch")
        return make_unique<CommandTouch>();
    if (name == "truncate")
        return make_unique<CommandTruncate>();
    if (name == "rm")
        return make_unique<CommandRm>();
    if (name == "wc")
        return make_unique<CommandWc>();
    if (name == "tr")
        return make_unique<CommandTr>();
    if (name == "head")
        return make_unique<CommandHead>();
    if (name == "batch")
        return make_unique<CommandBatch>();
    throw UknownCommandError(name);
}
