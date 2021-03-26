#pragma once

#ifndef TM_FILENAME_BASE 
#define TM_FILENAME_BASE 

#endif /* TM_FILENAME_BASE  */

namespace 
{
    namespace flags
    {
        /**
         * @brief Prüft, ob in einem Status eine Flagge gesetzt ist.
         *
         * @tparam TState Statustyp.
         * @tparam TArg Flaggentyp.
         * @param state Der Status.
         * @param flag Die Flagge.
         * @return true Die Flagge ist gesetzt.
         * @return false Die Flagge ist nicht gesetzt,
         */
        template <typename TState, typename TArg>
        constexpr bool Has(TState state, TArg flag)
        {
            return (state & static_cast<TState>(flag)) != TState{};
        }

        /**
         * @brief Prüft, ob in einem Status eine Flagge nicht gesetzt ist.
         *
         * @tparam TState Statustyp.
         * @tparam TArg Flaggentyp.
         * @param state Der Status.
         * @param flag Die Flagge.
         * @return true Die Flagge ist gesetzt.
         * @return false Die Flagge ist nicht gesetzt,
         */
        template <typename TState, typename TArg>
        constexpr bool HasNot(TState state, TArg flag)
        {
            return !Has(state, flag);
        }

        /**
         * @brief Prüft ob in einem Status alles Flaggen gesetzt sind.
         *
         * @tparam TState Statustyp.
         * @tparam TFirstArg Typ der ersten Flagge.
         * @tparam TArgs Typen der restlichen Flaggen, kann leer sein.
         * @param state Der Status.
         * @param firstArg Die erste Flagge.
         * @param args Die restlichen Flaggen, kann leer sein.
         * @return true Alle Flaggen sind gesetzt.
         * @return false Nicht alle Flaggen sind gesetzt.
         */
        template <typename TState, typename TFirstArg, typename... TArgs>
        constexpr bool HasAll(TState state, TFirstArg firstArg, TArgs... args)
        {
            if constexpr (sizeof...(args) > 0)
            {
                return Has(state, firstArg) && HasAll(state, args...);
            }
            else
            {
                return true;
            }
        }

        /**
         * @brief Prüft ob in einem Status mindestens eine Flaggen gesetzt ist.
         *
         * @tparam TState Statustyp.
         * @tparam TFirstArg Typ der ersten Flagge.
         * @tparam TArgs Typen der restlichen Flaggen, kann leer sein.
         * @param state Der Status.
         * @param firstArg Die erste Flagge.
         * @param args Die restlichen Flaggen, kann leer sein.
         * @return true Mindestens eine Flagge ist gesetzt.
         * @return false Keine der Flaggen ist gesetzt.
         */
        template <typename TState, typename TFirstArg, typename... TArgs>
        constexpr bool HasAny(TState state, TFirstArg firstArg, TArgs... args)
        {
            if constexpr (sizeof...(args) > 0)
            {
                return Has(state, firstArg) || HasAny(state, args...);
            }
            else
            {
                return false;
            }
        }

        /**
         * @brief Prüft ob in einem Status nicht alle Flaggen gesetzt sind.
         *
         * @tparam TState Statustyp.
         * @tparam TFirstArg Typ der ersten Flagge.
         * @tparam TArgs Typen der restlichen Flaggen, kann leer sein.
         * @param state Der Status.
         * @param firstArg Die erste Flagge.
         * @param args Die restlichen Flaggen, kann leer sein.
         * @return true Mindestens eine Flagge ist nicht gesetzt.
         * @return false Alle Flaggen sind gesetzt.
         */
        template <typename TState, typename TFirstArg, typename... TArgs>
        constexpr bool HasNotAll(TState state, TFirstArg firstArg, TArgs... args)
        {
            if constexpr (sizeof...(args) > 0)
            {
                return HasNot(state, firstArg) || HasNotAll(state, args...);
            }
            else
            {
                return false;
            }
        }

        /**
         * @brief Prüft ob in einem Status mindestens eine aber nicht alle Flaggen gesetzt sind.
         *
         * @tparam TState Statustyp.
         * @tparam TFirstArg Typ der ersten Flagge.
         * @tparam TArgs Typen der restlichen Flaggen, kann leer sein.
         * @param state Der Status.
         * @param firstArg Die erste Flagge.
         * @param args Die restlichen Flaggen, kann leer sein.
         * @return true Mindestens eine Flagge ist gesetzt und mindestens eine Flagge ist nicht gesetzt.
         * @return falseAlle Flaggen sind gesetzt oder keine Flagge ist gesetzt.
         */
        template <typename TState, typename TFirstArg, typename... TArgs>
        constexpr bool HasAnyButNotAll(TState state, TFirstArg firstArg, TArgs... args)
        {
            if constexpr (sizeof...(args) > 0)
            {
                return (Has(state, firstArg) && HasNotAll(state, args...)) ||
                    (HasNot(state, firstArg) && HasAny(state, args...));
            }
            else
            {
                return false;
            }
        }

        /**
         * @brief Prüft ob in einem Status keine der Flaggen gesetzt ist.
         *
         * @tparam TState Statustyp.
         * @tparam TFirstArg Typ der ersten Flagge.
         * @tparam TArgs Typen der restlichen Flaggen, kann leer sein.
         * @param state Der Status.
         * @param firstArg Die erste Flagge.
         * @param args Die restlichen Flaggen, kann leer sein.
         * @return true Mindestens eine Flagge ist gesetzt.
         * @return false Keine der Flaggen ist gesetzt.
         */
        template <typename TState, typename TFirstArg, typename... TArgs>
        constexpr bool HasNone(TState state, TFirstArg firstArg, TArgs... args)
        {
            if constexpr (sizeof...(args) > 0)
            {
                return HasNot(state, firstArg) && HasNone(state, args...);
            }
            else
            {
                return true;
            }
        }

        /**
         * @brief Klasse zum Wrappen einer Flagge.
         *
         * @tparam TBaseType Der Typ des Status.
         */
        template <typename TBaseType>
        class Flag
        {
        private:
            TBaseType state;
            bool good;

            /**
             * @brief Initialisiert eine neue Instanz der Klasse.
             *
             * @param state Der Status.
             * @param success Der Erfolgszustand (wenn dieser false ist schlagen alle Operationen fehl).
             */
            constexpr Flag(TBaseType state, bool success)
                : state(state),
                good(success)
            { }

        public:
            /**
             * @brief Initialisiert eine neue Instanz der Klasse.
             *
             * @param state Der Status.
             */
            constexpr Flag(TBaseType state)
                : state(state),
                good(true)
            { }

            /**
             * @brief Prüft ob die Flagge gesetzt ist.
             *
             * @tparam TArg Flaggentyp.
             * @param arg Die Flagge.
             * @return constexpr Flag Die resultierende Flag-Instanz..
             */
            template <typename TArg>
            constexpr Flag Has(TArg arg) const
            {
                return lib::flags::Has(this->state, arg)
                    ? *this
                    : Flag(this->state, false);
            }

            /**
             * @brief Prüft ob die Flagge nicht gesetzt ist.
             *
             * @tparam TArg Flaggentyp.
             * @param arg Die Flagge.
             * @return constexpr Flag Die resultierende Flag-Instanz..
             */
            template <typename TArg>
            constexpr Flag HasNot(TArg arg) const
            {
                return lib::flags::HasNot(this->state, arg)
                    ? *this
                    : Flag(this->state, false);
            }

            /**
             * @brief Prüft ob alle Flaggen gesetzt sind.
             *
             * @tparam TArgs Die Typen der Flaggen.
             * @param args Die Flaggen.
             * @return constexpr Flag Die resultierende Flag-Instanz.
             */
            template <typename... TArgs>
            constexpr Flag HasAll(TArgs... args) const
            {
                return this->good && lib::flags::HasAll(this->state, args...)
                    ? *this
                    : Flag(this->state, false);
            }

            /**
             * @brief Prüft ob mindestens eine Flagge gesetzt ist.
             *
             * @tparam TArgs Die Typen der Flaggen.
             * @param args Die Flaggen.
             * @return constexpr Flag Die resultierende Flag-Instanz.
             */
            template <typename... TArgs>
            constexpr Flag HasAny(TArgs... args) const
            {
                return this->good && lib::flags::HasAny(this->state, args...)
                    ? *this
                    : Flag(this->state, false);
            }

            /**
             * @brief Prüft ob mindetens eine Flaggen nicht gesetzt ist.
             *
             * @tparam TArgs Die Typen der Flaggen.
             * @param args Die Flaggen.
             * @return constexpr Flag Die resultierende Flag-Instanz.
             */
            template <typename... TArgs>
            constexpr Flag HasNotAll(TArgs... args) const
            {
                return this->good && lib::flags::HasNotAll(this->state, args...)
                    ? *this
                    : Flag(this->state, false);
            }

            /**
             * @brief Prüft ob mindestens eine aber nicht alle Flaggen gesetzt sind.
             *
             * @tparam TArgs Die Typen der Flaggen.
             * @param args Die Flaggen.
             * @return constexpr Flag Die resultierende Flag-Instanz.
             */
            template <typename... TArgs>
            constexpr Flag HasAnyButNotAll(TArgs... args) const
            {
                return this->good && lib::flags::HasAnyButNotAll(this->state, args...)
                    ? *this
                    : Flag(this->state, false);
            }

            /**
             * @brief Prüft ob keine der Flaggen gesetzt ist.
             *
             * @tparam TArgs Die Typen der Flaggen.
             * @param args Die Flaggen.
             * @return constexpr Flag Die resultierende Flag-Instanz.
             */
            template <typename TFirstArg, typename... TArgs>
            constexpr Flag HasNone(TFirstArg firstArg, TArgs... args) const
            {
                return this->good && lib::flags::HasNone(this->state, args...)
                    ? *this
                    : Flag(this->state, false);
            }

            /**
             * @brief Konvertiert die Instanz zu einem bool.
             *
             * @return true alle bisherigen Operationen waren erfolgreich.
             * @return false mindestens eine Operation war nicht erfolgreich.
             */
            constexpr operator bool() const
            {
                return this->good;
            }

            /**
             * @brief  Konvertiert die Instanz zu einem bool. (Wie operator bool, nur explizit)
             *
             * @return true alle bisherigen Operationen waren erfolgreich.
             * @return false mindestens eine Operation war nicht erfolgreich.
             */
            constexpr bool IsGood() const
            {
                return this->good;
            }
        };

        /**
         * @brief Erzeugt eine Flag-Instanz mit einem bestimmen Wert.
         *
         * @tparam T
         * @param value
         * @return Flag<T>
         */
        template <typename T>
        Flag<T> MakeFlag(T value)
        {
            return Flag<T>(value);
        }
    } // namespace flags
} // namespace lib
