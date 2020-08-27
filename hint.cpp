#define SIGNAL(signalname, ...) using signalname##Type = star::Signal<__VA_ARGS__>; mutable signalname##Type signalname
#define SLOT(class, signalname) class ::signalname##Type::ConnectionGuard