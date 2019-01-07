//
//  Enable.hpp
//  ElementalRoguelite
//
//  Created by Dylan Burden on 2018-09-24.
//  Copyright © 2018 ElementalRoguelike. All rights reserved.
//

#ifndef Enable_hpp
#define Enable_hpp

#include <algorithm>

namespace detail
{
    enum class enabler{};
    
    template< typename Condition >
    using enableIf = typename std::enable_if< Condition::value, detail::enabler >::type;
}


#endif /* Enable_hpp */
