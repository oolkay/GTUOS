#ifndef REGULAR_FILE_HPP
#define REGULAR_FILE_HPP

#include "File.hpp"

namespace FileSystem
{
    class RegularFile : public File
    {
        public:
            //NO PARAMETER CONSTRUCTOR
            RegularFile() = delete; //My design does not allow to use default constructor 

            //COPY CONSTRUCTOR
            RegularFile(const RegularFile& other) = default; //default is enough

            //= OPERATOR OVERLOAD
            RegularFile&            operator=(const RegularFile& other) = delete; //My design does not allow to use = operator

            //PARAMETERIZED CONSTRUCTOR
            // lastModified default olarak alinabilir kendi halledebilir içeride
            RegularFile(std::string name, std::string path, std::string lastModified, std::string content = "", size_t size = 0);

            //SETTERS
            void                    setContent(std::string content);
            void                    setSize(size_t size);

            //GETTERS
            inline std::string      getContent() const {return content;}
            inline size_t           getSize() const {return size;}

            //OVERLOADING OPERATORS
            friend std::ostream&    operator<<(std::ostream& os, const RegularFile& regFile);

            //FILE FUNCTIONS
            void                    ls() const override;
            void                    cat() const override;

            //ITERATOR FUNCTIONS
            class Iterator
                {
                public:
                    Iterator(std::string::iterator iterator) : current(iterator) {}

                    Iterator& operator++()
                    {
                        ++current;
                        return *this;
                    }

                    Iterator operator++(int)
                    {
                        Iterator tmp = *this;
                        ++current;
                        return tmp;
                    }

                    bool operator==(const Iterator& other) const
                    {
                        return current == other.current;
                    }

                    bool operator!=(const Iterator& other) const
                    {
                        return current != other.current;
                    }

                    char operator*() const
                    {
                        return *current;
                    }

                private:
                    std::string::iterator current;
                };

            Iterator begin()
            {
                return Iterator(content.begin());
            }

            Iterator end()
            {
                return Iterator(content.end());
            }

            //DESTRUCTOR
            ~RegularFile();

        private:
            std::string content;
            size_t      size;
    };
}

#endif