using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.CompilerServices;
using System.Text;

namespace Script.Log
{
    /**
    * https://github.com/mono-ue/UnrealEngine/blob/monoue/Engine/Plugins/MonoUE/Managed/MonoBindings/LogTextWriter.cs
    */
    sealed class Log : TextWriter
    {
        private sealed class StringWrapper : IList<char>
        {
            public string String;

            public char this[int index]
            {
                get => String[index];
                set => throw new NotImplementedException();
            }

            public int IndexOf(char item)
            {
                throw new NotImplementedException();
            }

            public void Insert(int index, char item)
            {
                throw new NotImplementedException();
            }

            public void RemoveAt(int index)
            {
                throw new NotImplementedException();
            }

            public void Add(char item)
            {
                throw new NotImplementedException();
            }

            public void Clear()
            {
                throw new NotImplementedException();
            }

            public bool Contains(char item)
            {
                throw new NotImplementedException();
            }

            public void CopyTo(char[] array, int arrayIndex)
            {
                throw new NotImplementedException();
            }

            public int Count => throw new NotImplementedException();

            public bool IsReadOnly => throw new NotImplementedException();

            public bool Remove(char item)
            {
                throw new NotImplementedException();
            }

            public IEnumerator<char> GetEnumerator()
            {
                throw new NotImplementedException();
            }

            System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
            {
                throw new NotImplementedException();
            }
        }

        private const uint MaxLineLength = 1024;

        private readonly char[] _storage = new char[MaxLineLength];

        private readonly char[] _tempStorage = new char[MaxLineLength + 1];

        private readonly StringWrapper _wrapper = new StringWrapper();

        private readonly char[] _tempSingleCharacterArray = new char[1];

        private uint _readIndex;

        private uint _writeIndex;

        private Log()
        {
        }

        private static TextWriter Create()
        {
            return Synchronized(new Log());
        }

        public override Encoding Encoding => Encoding.Default;

        public override void Flush()
        {
            InternalFlush(false);
        }

        public override void Write(char value)
        {
            _tempSingleCharacterArray[0] = value;

            WriteInternal(_tempSingleCharacterArray, 0, 1);
        }

        public override void Write(string value)
        {
            _wrapper.String = value;

            WriteInternal(_wrapper, 0, value.Length);

            _wrapper.String = null;
        }

        public override void Write(char[] buffer, int index, int count)
        {
            WriteInternal(buffer, index, count);
        }

        private void WriteInternal<T>(T buffer, int index, int count) where T : IList<char>
        {
            var endIndex = index + count;

            for (var i = index; i < endIndex; ++i)
            {
                switch (buffer[i])
                {
                    case '\0':
                        throw new ArgumentException(
                            "LogTextWriter does not support null terminators in the middle of a written buffer");
                    case '\n':
                    case '\r':
                        InternalFlush(false);
                        break;
                    default:
                        _storage[_writeIndex] = buffer[i];

                        AdvanceWritePointer();

                        break;
                }
            }
        }

        private void InternalFlush(bool bufferFull)
        {
            if (_readIndex == _writeIndex && !bufferFull)
            {
                return;
            }

            if (_readIndex < _writeIndex)
            {
                _storage[_writeIndex] = '\0';

                LogImplementation(_storage, _readIndex);
            }
            else
            {
                var firstBlockCount = MaxLineLength - _readIndex;

                Array.Copy(_storage, _readIndex, _tempStorage, 0, firstBlockCount);

                Array.Copy(_storage, 0, _tempStorage, firstBlockCount, _writeIndex);

                _tempStorage[firstBlockCount + _writeIndex] = '\0';

                LogImplementation(_tempStorage, 0);
            }

            _readIndex = _writeIndex;
        }

        private void AdvanceWritePointer()
        {
            _writeIndex = (_writeIndex + 1) % MaxLineLength;

            if (_writeIndex == _readIndex)
            {
                InternalFlush(true);
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void LogImplementation(char[] InBuffer, uint InReadOffset);

        public static void SetOut()
        {
            Console.SetOut(Create());
        }
    }
}