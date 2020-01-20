#include <string>

#include "args.hpp"

using namespace args;

int main(int argc, char *argv[]) {

    using Timeout = char_marker<'T'>;
    using File = char_marker<'f'>;

    Args<Timeout, long, File, std::string> args{};

    auto t = args.get<Timeout>();
    auto f = args.get<File>();

    return 0;
}

