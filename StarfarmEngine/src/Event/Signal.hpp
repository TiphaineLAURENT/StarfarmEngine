//
// Created by Tiphaine LAURENT on 20/08/2019.
//

#ifndef STARFARMENGINE_SIGNAL_HPP
#define STARFARMENGINE_SIGNAL_HPP

#include <algorithm>
#include <functional>
#include <list>
#include <memory>
#include <ostream>

#include "util.hpp"

namespace star
{
#define SIGNAL(signalname, ...)                             \
        using signalname##Type = star::Signal<__VA_ARGS__>; \
        mutable signalname##Type signalname
#define SLOT(class, signalname) class ::signalname##Type::ConnectionGuard

        template <class... ARGS> class Signal
        {
                // ATTRIBUTES
            public:
                using Callback = std::function<void(ARGS...)>;

                class Connection;

                class ConnectionGuard;

            private:
                struct Slot
                {
                        explicit Slot(ecs::NonOwningPointer<Signal> signal, Callback &&callback)
                                : _signal{ signal }, _callback{ std::move(callback) }
                        {}

                        bool operator==(const Slot &other) const { return this == &other; }

                        Callback _callback{};

                        ecs::NonOwningPointer<Signal> _signal{ nullptr };
                };

                using SlotPtr = std::shared_ptr<Slot>;
                using SlotList = std::list<SlotPtr>;

                // METHODS
            public:    // CONSTRUCTORS
                Signal() = default;
                ~Signal() = default;
                Signal(const Signal &copy) = default;
                Signal(Signal &&) noexcept = default;

            public:    // OPERATORS
                Signal &operator=(const Signal &other) = default;
                Signal &operator=(Signal &&) noexcept = default;

                void operator()(ARGS... args)
                {
                        for (auto &slot : _slots)
                        {
                                slot->_callback(args...);
                        }
                }

            public:
                void clear() { _slots.clear(); }

                Connection connect(const Callback &callback)
                {
                        return connect(Callback{ callback });
                }
                Connection connect(Callback &&callback)
                {
                        auto slot = std::make_shared<Slot>(this, std::move(callback));
                        _slots.push_back(std::move(slot));
                        return Connection{ _slots.back() };
                }
                template <class O> Connection connect(O &object, void (O::*method)(ARGS...))
                {
                        return connect([&object, &method](Args &&... args) {
                                return std::invoke(method, object, std::forward<Args>(args)...);
                        });
                }
                template <class O> Connection connect(O *object, void (O::*method)(ARGS...))
                {
                        return connect([&object, &method](Args &&... args) {
                                return std::invoke(method, object, std::forward<Args>(args)...);
                        });
                }
                template <class O>
                Connection connect(const O &object, void (O::*method)(ARGS...) const)
                {
                        return connect([&object, &method](Args &&... args) {
                                return std::invoke(method, object, std::forward<Args>(args)...);
                        });
                }
                template <class O>
                Connection connect(const O *object, void (O::*method)(ARGS...) const)
                {
                        return connect([&object, &method](Args &&... args) {
                                return std::invoke(method, object, std::forward<Args>(args)...);
                        });
                }

                void disconnect(const Slot &slot)
                {
                        _slots.erase(std::remove_if(
                                _slots.begin(), _slots.end(), [&slot](const SlotPtr &slotPtr) {
                                        return *slotPtr == slot;
                                }));
                }

            private:
                SlotList _slots;
        };

        template <class... ARGS>
        std::ostream &operator<<(std::ostream &out, const Signal<ARGS...> &);

        template <class... Args> class Signal<Args...>::Connection
        {
                using SignalHandler = Signal<Args...>;
                friend SignalHandler;

            public:
            private:
                std::weak_ptr<Slot> _slot;

            public:
                Connection() = default;
                Connection(const Connection &connection) = default;
                Connection(Connection &&connection) noexcept = default;
                ~Connection() = default;

            public:
                Connection &operator=(const Connection &connection) = default;
                Connection &operator=(Connection &&connection) noexcept
                {
                        _slot = std::move(connection._slot);
                        connection._slot.reset();

                        return *this;
                }

            public:
                template <class... ConnectArgs>
                void connect(SignalHandler &signal, ConnectArgs &&... args)
                {
                        operator=(signal.connect(std::forward<ConnectArgs>(args)...));
                }
                void disconnect() noexcept
                {
                        if (auto ptr = _slot.lock())
                        {
                                ptr->_signal->disconnect(*ptr);
                        }
                }

                [[nodiscard]] bool is_connected() const { return _slot.expired(); }

            private:
                explicit Connection(const SlotPtr &slot) : _slot(slot) {}
        };

        template <class... Args> class Signal<Args...>::ConnectionGuard
        {
                using SignalHandler = Signal<Args...>;
                using Connection = typename SignalHandler::Connection;

            public:
            private:
                Connection _connection;

            public:
                ConnectionGuard() = default;
                explicit ConnectionGuard(const Connection &connection) : _connection(connection) {}
                ConnectionGuard(const ConnectionGuard &connection) = delete;
                explicit ConnectionGuard(Connection &&connection)
                        : _connection(std::move(connection))
                {}
                ConnectionGuard(ConnectionGuard &&connection) noexcept = default;
                ~ConnectionGuard() { _connection.disconnect(); }

            public:
                ConnectionGuard &operator=(const Connection &connection)
                {
                        disconnect();
                        _connection = connection;
                        return *this;
                }
                ConnectionGuard &operator=(const ConnectionGuard &connection) = delete;
                ConnectionGuard &operator=(Connection &&connection)
                {
                        disconnect();
                        _connection = std::move(connection);
                        return *this;
                }
                ConnectionGuard &operator=(ConnectionGuard &&connection) noexcept
                {
                        disconnect();
                        _connection = std::move(connection);
                        return *this;
                }

            public:
                template <class... ConnectArgs>
                void connect(SignalHandler &signal, ConnectArgs &&... args)
                {
                        disconnect();
                        _connection.connect(signal, std::forward<ConnectArgs>(args)...);
                }
                void disconnect() noexcept { _connection.disconnect(); }

                [[nodiscard]] Connection &get_connection() { return _connection; }

                [[nodiscard]] bool is_connected() const { return _connection.is_connected(); }

            private:
        };
}    // namespace star

#endif    // STARFARMENGINE_SIGNAL_HPP
