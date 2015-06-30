#include "FS.h"

int comp(char *a, char *b)
{
    return strcmp(a, b);
}

void FS::clear(FS::Descriptor *fd)
{
    for (int i = 0; i < BLOCKS_PER_FILE; ++i)
    {
        fd->disk_map[i] = -1;
    }
    fd->length = -1;
}

FS::Descriptor *FS::get_descriptor(int index, unsigned char *block)
{
    int byte_num = index * sizeof(Descriptor);
    disk.read_block(byte_num / LDisk::BLOCK_SIZE + 1, block);
    return (Descriptor *)(&block[byte_num % LDisk::BLOCK_SIZE]);
}

void FS::write_descriptor(int index, unsigned char *block)
{
    disk.write_block((index * sizeof(FS::Descriptor)) / LDisk::BLOCK_SIZE + 1, block);
}

char *FS::create(char *file_name)
{
    if (strlen(file_name) > FS::MAX_NAME_LENGTH - 1)
    {
        return "File name is too long";
    }
    // Find a free file descriptor
    Descriptor *free_descr = nullptr;
    int free_id;
    unsigned char block[LDisk::BLOCK_SIZE];
    for (int i = 1; i <= FS::BLOCKS_RESERVED && free_descr == nullptr; ++i)
    {
        disk.read_block(i, block);
        for (int j = 0; j < LDisk::BLOCK_SIZE && free_descr == nullptr; j += sizeof(Descriptor))
        {
            Descriptor *cur = (Descriptor *)(&block[j]);
            if (cur->length == -1)
            {
                free_descr = cur;
                free_id = ((i - 1) * LDisk::BLOCK_SIZE + j) / sizeof(Descriptor);
            }
        }
    }
    if (free_descr == nullptr)
    {
        return "No free descriptor";
    }
    __lseek(0, 0, false);
    // Find a free directory entry
    FileEntry file_entry;
    FileEntry new_file;
    memcpy(new_file.name, file_name, sizeof(new_file.name));
    new_file.index = free_id;
    // check for duplicate file name
    while (true)
    {
        int r = read(0, (unsigned char *)(&file_entry), sizeof(FileEntry));
        if (!r)
            break;
        if (file_entry.index != -1 && comp(file_entry.name, file_name) == 0)
        {
            return "Duplicate file name";
        }
    }
    __lseek(0, 0, false);
    while (true)
    {
        int r = read(0, (unsigned char *)(&file_entry), sizeof(FileEntry));
        // If no entries left or empty one found
        if (r == 0 || file_entry.index == -1)
        {
            __lseek(0, OFT[0].pos - r, false);
            // try to write new file entry
            r = write(0, (unsigned char *)(&new_file), sizeof(FileEntry));
            if (r <= 0)
            {
                return "No free space in folder";
            }
            break;
        }
    }
    // fill descriptor entry
    free_descr = get_descriptor(free_id, block);
    clear(free_descr);
    free_descr->length = 0;
    write_descriptor(free_id, block);
    //disk.write_block((free_id * sizeof(Descriptor)) / LDisk::BLOCK_SIZE + 1, block);
    return nullptr;
}

char *FS::destroy(char *file_name)
{
    __lseek(0, 0, false);
    // search directory to find file descriptor
    FileEntry file_entry;
    int index = -1;
    while (true)
    {
        int r = read(0, (unsigned char *)(&file_entry), sizeof(FileEntry));
        if (r == 0)
        {
            return "No file with such name";
        }
        if (comp(file_entry.name, file_name) == 0)
        {
            // remember index and remove directory entry
            __lseek(0, OFT[0].pos - r, false);
            index = file_entry.index;
            file_entry.index = -1;
            write(0, (unsigned char *)(&file_entry), sizeof(FileEntry));

            break;
        }
    }
    if (index == -1)
    {
        return "No file with such name";
    }

    for (int i = 0; i < FS::OFT_SIZE; i++)
    {
        if (OFT[i].index == index)
        {
            close(i);
            break;
        }
    }

    unsigned char block[LDisk::BLOCK_SIZE];
    Descriptor *file_descr = get_descriptor(index, block);

    unsigned char bitmap[LDisk::BLOCK_SIZE];
    disk.read_block(0, bitmap);

    // update bit map (if file was not empty)
    for (int i = 0; i < FS::BLOCKS_PER_FILE; ++i)
    {
        int block_id = file_descr->disk_map[i];
        if (block_id != -1)
            unset_bit(block_id, bitmap);
    }
    // free file descriptor
    clear(file_descr);
    write_descriptor(index, block);
    //disk.write_block((index * sizeof(Descriptor)) / LDisk::BLOCK_SIZE + 1, block);
    disk.write_block(0, bitmap);
    return nullptr;
}

int FS::open(char *file_name)
{
    if (strlen(file_name) > FS::MAX_NAME_LENGTH - 1)
    {
        return -1;
    }
    __lseek(0, 0, false);
    // search directory to find index of file descriptor (index)
    FileEntry file_entry;
    int index = -1;
    while (true)
    {
        int r = read(0, (unsigned char *)(&file_entry), sizeof(FileEntry));
        if (r == 0)
        {
            return -1;
        }
        if (comp(file_entry.name, file_name) == 0)
        {
            index = file_entry.index;
            break;
        }
    }
    if (index == -1)
    {
        return -1;
    }

    // find free OFT entry
    int oft_entry = -1;
    for (int i = 0; i < FS::OFT_SIZE; ++i)
    {
        if (OFT[i].index == index)
        {
            return i;
        }
        if (oft_entry == -1 && OFT[i].index == -1)
        {
            oft_entry = i;
        }
    }
    if (oft_entry == -1)
    {
        return -1;
    }

    // Get file's descriptor
    unsigned char block[LDisk::BLOCK_SIZE];
    Descriptor *file_descr = get_descriptor(index, block);

    // Fill OFT entry
    // fill in current position (0) and file descriptor index (i)
    OFT[oft_entry].length = file_descr->length;
    OFT[oft_entry].index = index;
    OFT[oft_entry].pos = 0;
    // read block 0 of file into the r/w buffer (read-ahead)
    if (file_descr->length > 0)
    {
        disk.read_block(file_descr->disk_map[0], OFT[oft_entry].buffer);
    }
    // return status
    return oft_entry;
}

char *FS::close(int oft_index)
{
    // Check if file is open
    if (oft_index < 0 || oft_index >= FS::OFT_SIZE || OFT[oft_index].index == -1)
    {
        return "No open file with such OFT index";
    }
    unsigned char block[LDisk::BLOCK_SIZE];
    Descriptor *file_descr = get_descriptor(OFT[oft_index].index, block);
    // Write buffer to disk
    if (OFT[oft_index].pos == OFT[oft_index].length && OFT[oft_index].pos)
    {
        --OFT[oft_index].pos;
    }
    int block_id = file_descr->disk_map[OFT[oft_index].pos / LDisk::BLOCK_SIZE];
    disk.write_block(block_id, OFT[oft_index].buffer);

    // update file length in descriptor
    file_descr->length = OFT[oft_index].length;
    // save file descriptor to disk
    write_descriptor(OFT[oft_index].index, block);
    //disk.write_block((OFT[oft_index].index * sizeof(Descriptor)) / LDisk::BLOCK_SIZE + 1, block);
    // free OFT entry
    OFT[oft_index].index = -1;

    // return status
    return nullptr;
}

int FS::read(int oft_index, unsigned char *dest, int count)
{
    if (oft_index < 0 || oft_index >= FS::OFT_SIZE || OFT[oft_index].index == -1)
    {
        return -1;
    }
    // read not more than left in the file
    count = min(count, OFT[oft_index].length - OFT[oft_index].pos);
    // get file descriptor
    unsigned char block[LDisk::BLOCK_SIZE];
    Descriptor *file_descr = get_descriptor(OFT[oft_index].index, block);

    for (int i = 0; i < count; ++i)
    {
        int pos = OFT[oft_index].pos % LDisk::BLOCK_SIZE;
        *dest++ = OFT[oft_index].buffer[pos];
        // move pointer without allocating new buffers
        __lseek(oft_index, OFT[oft_index].pos + 1, false);
    }
    return count;
}

int FS::write(int oft_index, unsigned char *src, int count)
{
    if (oft_index < 0 || oft_index >= FS::OFT_SIZE || OFT[oft_index].index == -1)
    {
        return -1;
    }
    // get file descriptor
    unsigned char block[LDisk::BLOCK_SIZE];
    Descriptor *file_descr = get_descriptor(OFT[oft_index].index, block);

    count = min(count, FS::BLOCKS_PER_FILE * LDisk::BLOCK_SIZE - OFT[oft_index].pos);
    for (int i = 0; i < count; ++i)
    {
        int pos = OFT[oft_index].pos % LDisk::BLOCK_SIZE;
        unsigned char old = OFT[oft_index].buffer[pos];
        OFT[oft_index].buffer[pos] = *src++;

        // move pointer and try to expand file
        if (__lseek(oft_index, OFT[oft_index].pos + 1, i != count - 1) != nullptr)
        {
            // if failed to expand - writing done
            OFT[oft_index].buffer[pos] = old;
            return i;
        }
    }
    return count;
}

bool FS::__expand(int oft_index, int new_length)
{
    unsigned char block[LDisk::BLOCK_SIZE];
    Descriptor *file_descr = get_descriptor(OFT[oft_index].index, block);

    unsigned char bitmap[LDisk::BLOCK_SIZE];
    disk.read_block(0, bitmap);
    bool expanded = false;

    while (new_length > OFT[oft_index].length && OFT[oft_index].length < FS::BLOCKS_PER_FILE * LDisk::BLOCK_SIZE)
    {
        // need new block
        if (OFT[oft_index].length % LDisk::BLOCK_SIZE == 0)
        {
            bool found = false;
            for (int i = 0; i < LDisk::BLOCK_CNT; ++i)
            {
                if (!get_bit(i, bitmap))
                {
                    unsigned char bl[LDisk::BLOCK_SIZE];
                    memcpy(bl, OFT[oft_index].buffer, sizeof(bl));
                    // if expanding directory - clear entries
                    if (oft_index == 0)
                    {
                        for (int j = 0; j < LDisk::BLOCK_SIZE; j += sizeof(FileEntry))
                        {
                            FileEntry *file_entry = (FileEntry *)(&bl[j]);
                            file_entry->index = -1;
                        }
                    }
                    disk.write_block(i, bl);
                    expanded = true;
                    // free block found
                    file_descr->disk_map[OFT[oft_index].length / LDisk::BLOCK_SIZE] = i;
                    set_bit(i, bitmap);
                    found = true;
                    break;
                }
            }
            if (!found)
                break;
        }
        ++OFT[oft_index].length;
    }

    // write bitmap back to disk
    disk.write_block(0, bitmap);

    write_descriptor(OFT[oft_index].index, block);
    return expanded;
}

char *FS::__lseek(int oft_index, int new_pos, bool expand)
{
    if (new_pos > FS::BLOCKS_PER_FILE * LDisk::BLOCK_SIZE - expand)
    {
        return "Out of bounds";
    }
    if (OFT[oft_index].pos == OFT[oft_index].length && OFT[oft_index].pos)
    {
        --OFT[oft_index].pos;
    }
    int cur_block_id = OFT[oft_index].pos / LDisk::BLOCK_SIZE;
    int new_block_id = new_pos / LDisk::BLOCK_SIZE;

    if (new_pos >= OFT[oft_index].length && !expand)
    {
        OFT[oft_index].pos = OFT[oft_index].length;
        return nullptr;
    }

    // new index is out of the current block
    // if it's not within file - expand
    bool expanded = false;
    bool need_expand = OFT[oft_index].length == 0 || new_pos / LDisk::BLOCK_SIZE > (OFT[oft_index].length - 1) / LDisk::BLOCK_SIZE;
    if (expand)
    {
        expanded = __expand(oft_index, new_pos + 1);
    }

    if (need_expand && !expanded)
    {
        return "out of space";
    }

    unsigned char block[LDisk::BLOCK_SIZE];
    Descriptor *file_descr = get_descriptor(OFT[oft_index].index, block);

    // new index is not within current block
    if (cur_block_id != new_block_id)
    {
        // write current block to disk
        disk.write_block(file_descr->disk_map[cur_block_id], OFT[oft_index].buffer);
    }
    if (expanded || cur_block_id != new_block_id)
    {
        // read new block from disk to buffer
        disk.read_block(file_descr->disk_map[new_block_id], OFT[oft_index].buffer);
    }
    OFT[oft_index].pos = min(new_pos, OFT[oft_index].length);
    return nullptr;
}

char *FS::lseek(int oft_index, int new_pos)
{
    if (oft_index <= 0 || oft_index >= FS::OFT_SIZE || OFT[oft_index].index == -1)
    {
        return "Access denied";
    }
    return __lseek(oft_index, new_pos, false);
}

char *FS::directory()
{
    char *res = new char[FS::BLOCKS_RESERVED * LDisk::BLOCK_SIZE];
    char *ptr = res;

    __lseek(0, 0, false);
    // search directory to find index of file descriptor (index)
    FileEntry file_entry;
    int index = -1;
    while (true)
    {
        int r = read(0, (unsigned char *)(&file_entry), sizeof(FileEntry));
        if (r == 0)
        {
            break;
        }
        if (file_entry.index != -1)
        {
            strcpy(ptr, file_entry.name);
            ptr += strlen(file_entry.name);
            *ptr++ = ' ';
        }
    }
    *ptr = 0;
    return res;
}

void FS::init(const char *file_name)
{
    FILE *inf = nullptr;
    for (int i = 0; i < FS::OFT_SIZE; ++i)
    {
        OFT[i].index = -1;
    }

    if (file_name == nullptr || (inf = fopen(file_name, "r+b")) == NULL)
    {
        // init here
        unsigned char block[LDisk::BLOCK_SIZE];
        memset(block, 0, sizeof(block));
        for (int i = 0; i <= FS::BLOCKS_RESERVED; ++i)
        {
            set_bit(i, block);
        }
        disk.write_block(0, block);
        Descriptor *file_descr;
        for (int i = 1; i <= FS::BLOCKS_RESERVED; ++i)
        {
            for (int j = 0; j < LDisk::BLOCK_SIZE; j += sizeof(Descriptor))
            {
                file_descr = (Descriptor *)(&block[j]);
                clear(file_descr);
                file_descr->length = (i + j == 1 ? 0 : -1);
            }
            disk.write_block(i, block);
        }
    }
    else
    {
        for (int i = 0; i < LDisk::BLOCK_CNT; ++i)
        {
            unsigned char block[LDisk::BLOCK_SIZE];
            fread(block, sizeof(unsigned char), LDisk::BLOCK_SIZE, inf);
            disk.write_block(i, block);
        }
        fclose(inf);
    }
    // Open directory
    unsigned char block[LDisk::BLOCK_SIZE];
    Descriptor *file_descr = get_descriptor(0, block);

    OFT[0].length = file_descr->length;
    OFT[0].index = 0;
    OFT[0].pos = 0;
    if (file_descr->length > 0)
    {
        disk.read_block(file_descr->disk_map[0], OFT[0].buffer);
    }
}

void FS::save(const char *file_name)
{
    for (int i = 0; i < FS::OFT_SIZE; ++i)
    {
        if (OFT[i].index != -1)
        {
            unsigned char block[LDisk::BLOCK_SIZE];
            Descriptor *file_descr = get_descriptor(OFT[i].index, block);
            file_descr->length = OFT[i].length;
            write_descriptor(OFT[i].index, block);
            if (OFT[i].pos == OFT[i].length && OFT[i].pos)
            {
                --OFT[i].pos;
            }
            int block_num = OFT[i].pos / LDisk::BLOCK_SIZE;
            if (file_descr->length != 0)
            {
                disk.write_block(file_descr->disk_map[block_num], OFT[i].buffer);
            }
        }
    }
    FILE *out = fopen(file_name, "w+b");

    for (int i = 0; i < LDisk::BLOCK_CNT; ++i)
    {
        unsigned char block[LDisk::BLOCK_SIZE];
        disk.read_block(i, block);
        fwrite(block, sizeof(unsigned char), LDisk::BLOCK_SIZE, out);
    }

    fclose(out);
}