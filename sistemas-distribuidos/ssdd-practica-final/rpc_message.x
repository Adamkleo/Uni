struct PrintArgs {
    opaque operation[256];
    opaque username[256];
    opaque date[256];
    opaque file[256];
};

program SERVER_OPERATION {
    version SERVER_OPERATION_VERS {
        void print(struct PrintArgs args) = 0;
    } = 1;
} = 99;
