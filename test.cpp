bool operator()(HuffTree* a, HuffTree* b) {
            // a : 1 -> d : 1 -> A : 1 -> B : 1 -> D : 1 -> c : 2 -> C : 2 -> D : 3
            // if frequency a == frequency b -> a > b
            // if same character -> a > A
            if (a->getweight() == b->getweight()) // bằng nhau
            {
                if (a->getroot()->isLeafType() && b->getroot()->isLeafType()) //2 lá
                {
                    // check ascii a > b
                    if (islower(a->getroot()->getvalue()) && islower(b->getroot()->getvalue())
                    || isupper(a->getroot()->getvalue()) && isupper(b->getroot()->getvalue())){
                        return a->getroot()->getvalue() > b->getroot()->getvalue(); // đúng là ra sau // lớn là ra sau
                    }
                    // check ascii a > A hay // A nhỏ hơn // A ra sau
                    else {
                        return a->getroot()->getvalue() < b->getroot()->getvalue();
                    }
                }
                else if (a->getroot()->isLeafType() && !b->getroot()->isLeafType()) // b ko phải leaf, b ra sau
                {   
                    // cho a ra trước
                    return false;
                }
                else if (!a->root()->isLeaf() && b->root()->isLeaf()) // a ko phải leaf, a ra sau
                {   
                    // cho b ra trước
                    return true;
                }
                else // cả 2 ko phải leaf, thằng chèn ra sau (a)
                {
                    // cho a ra sau
                    return true;
                }
            }
            // frequecy a < frequency b
            return a->weight() >= b->weight();
        }