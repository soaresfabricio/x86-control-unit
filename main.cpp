#include <fstream>
#include <iomanip>
#include "include/Registers.hpp"
#include "include/Decoder.hpp"
#include "include/Memory.hpp"
#include "include/Instruction.hpp"
#include "include/Label.hpp"
#include "include/Word.hpp"
#include "include/Data.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Decoder dec;
    Registers regs;
    Label lbls;
    Memory mem;

    Data *data = new Data(1000);
    *data = 0;
    mem.insert(data);

    Data *data2 = new Data(992);
    *data2 = 0;
    mem.insert(data2);

    ifstream inf(argv[1]);
    inf >> mem;
    inf.clear();
    inf.seekg(0);
    inf >> lbls;

    regs.set(Registers::eip, lbls.find("main"));

    regs.load_from_file("registers.txt");

    int cycles = 0;

    while (regs.get(Registers::eip) != 0)
    {
        const Instruction &inst = mem.fetch(&regs);
        dec.parse(inst, &regs, mem, lbls);
        dec.execute(inst, &regs, mem);
        cout << inst << regs;
        cycles++;
    }

    cout << "Number of cycles: " << cycles << endl;

    ofstream output("stack.txt");
    if (output.is_open())
    {
        cout << "Saving stack to the file stack.txt";

        for (size_t i = 1000; i > 0; i = i - 4)
        {

            try
            {
                Data &data = dynamic_cast<Data &>(mem[i]);
                output << i << ": " << data.get() << endl;
            }
            catch (const std::bad_cast &e)
            {
                output << i << ": " << 0 << endl;
            }
        }
        cout << "... DONE" << endl;
    }
    else
    {
        cout << "There was a problem opening stack.txt " << endl;
    }


    regs.dump_to_file("registers.txt");
    return 0;
}
