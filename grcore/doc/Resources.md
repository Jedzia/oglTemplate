Possible ways to link resources.

## Linux

### objcopy
see https://stackoverflow.com/a/4865249/1530424

**Update** I have grown to prefer the control [John Ripley's assembly `.incbin` based solution][1] offers and now use a variant on that. This is described in the following under the topic **"GNU assembler"**.

I have used objcopy (GNU binutils) to link the binary data from a file foo-data.bin into the data section of the executable:

    objcopy -B i386 -I binary -O elf32-i386 foo-data.bin foo-data.o

This gives you a `foo-data.o` object file which you can link into your executable. The C interface looks something like

    /** created from binary via objcopy */
    extern uint8_t foo_data[]      asm("_binary_foo_data_bin_start");
    extern uint8_t foo_data_size[] asm("_binary_foo_data_bin_size");
    extern uint8_t foo_data_end[]  asm("_binary_foo_data_bin_end");

so you can do stuff like

    for (uint8_t *byte=foo_data; byte<foo_data_end; ++byte) {
        transmit_single_byte(*byte);
    }

or

    size_t foo_size = (size_t)((void *)foo_data_size);
    void  *foo_copy = malloc(foo_size);
    assert(foo_copy);
    memcpy(foo_copy, foo_data, foo_size);

If your target architecture has special constraints as to where constant and variable data is stored, or you want to store that data in the `.text` segment to make it fit into the same memory type as your program code, you can play with the `objcopy` parameters some more.


  [1]: https://stackoverflow.com/a/4910421/182675 "John Ripley's assembly `.incbin` based solution"

### LD
see https://stackoverflow.com/a/11622727/1530424

You can embed binary files in executable using `ld` linker.
For example, if you have file `foo.bar` then you can embed it in executable adding the following commands to `ld`

    --format=binary foo.bar --format=default

If you are invoking `ld` thru `gcc` then you will need to add `-Wl`

    -Wl,--format=binary -Wl,foo.bar -Wl,--format=default

Here `--format=binary` tells the linker that the following file is binary and `--format=default` switches back to default input format (this is usefull if you will specify other input files after `foo.bar`).

Then you can access content of your file from code:

    extern uint8_t data[]     asm("_binary_foo_bar_start");
    extern uint8_t data_end[] asm("_binary_foo_bar_end");

There is also symbol named `"_binary_foo_bar_size"`. I think it is of type `uintptr_t` but i didn't check it.

### GNU assembler
see https://stackoverflow.com/a/4910421/1530424

If you want control over the exact symbol name and placement of resources, you can use (or script) the GNU assembler (not really part of gcc) to import whole binary files. Try this:

Assembly (x86/arm):

        .section .rodata
    	.global thing
        .type   thing, @object
        .align  4
    thing:
        .incbin "meh.bin"
    thing_end:
        .global thing_size
        .type   thing_size, @object
        .align  4
    thing_size:
    	.int    thing_end - thing

C:

    #include <stdio.h>
    extern char thing[];
    extern unsigned thing_size;
    int main() {
      printf("%p %u\n", thing, thing_size);
      return 0;
    }

Whatever you use, it's probably best to make a script to generate all the resources, and have nice/uniform symbol names for everything.