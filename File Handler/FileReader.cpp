//
// Created by Amr Hendy on 12/5/2018.
//

#include "FileReader.h"

FileReader::FileReader(string file_path, int chunk_size) {
    FileReader::file = fopen(file_path, 'rb');
    FileReader::chunk_size = chunk_size;
    FileReader::current_chunk_index = 0;
}

FileReader::~FileReader() {
    fclose(file);
    free(this);
}

int FileReader::get_file_size() {
    fseek(file, 0, SEEK_END);
    int x = ftell(file);
    rewind(file);
    return x;
}

int FileReader::get_current_chunk_index() {
    return current_chunk_index;
}

string FileReader::get_current_chunk_data() {
    if(is_finished()){
        perror("No remaining bytes to be read");
    }
    current_chunk_index++;
    return get_chunk_data(current_chunk_index - 1);
}

void FileReader::advance_chunk_pointer() {
    current_chunk_index++;
}

string FileReader::get_chunk_data(int chunk_index) {
    if(chunk_index * chunk_size >= get_file_size()){
        perror("No remaining bytes to be read");
    }
    fseek(FileReader::file, chunk_index * chunk_size, SEEK_SET);
    char * buffer = (char*) malloc(chunk_size)
    int bytes_readed = fread (buffer, sizeof(char), sizeof(buffer), file);
    if(bytes_readed != chunk_size && ftell(file) != SEEK_END){
        perror("Reading File Error");
    }
    return string(buffer);
}

bool FileReader::is_finished(){
    return ftell(file) == SEEK_END;
}