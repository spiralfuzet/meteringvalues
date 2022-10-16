#pragma once

namespace supercharge::meteringvalues::visitor {

template<typename... Ts>                                                 
struct VisitorComposite : Ts... { 
    using Ts::operator()...;
};

template<class... Ts> VisitorComposite(Ts...) -> VisitorComposite<Ts...>;

} // namespace supercharge::meteringvalues::visitor
