template<typename T>
std::ostream& operator<<(std::ostream& ost, std::vector<T>& vec) {
    ost << '(';
    for (int i = 0; i < vec.size(); ++i) //wypisywanie przecinków tylko do przedostatniego elementu
    {
        ost << vec[i];
        if (i != vec.size() - 1)
            ost << ", ";
    }
    ost << ')';
    return ost;
}