namespace stonesCalc {

    public class StonesCalc {

        public List<(long, long)> Stones { get; set; }

        public StonesCalc(string input) {
            Stones = new List<(long, long)>();

            foreach (string number in input.Split(" ")) {
                long numberLong = long.Parse(number);
                Stones.Add((numberLong, 1));
            }
        }

        public void Blink() {
            // process reverse
            for (int i = Stones.Count() - 1; i >= 0; i--) {
                // process stone

                // rule 1 = if number is 0 then make it 1
                if (Stones[i].Item1 == 0) {
                    Stones[i] = (1, Stones[i].Item2);
                } else if (Stones[i].Item1.ToString().Length % 2 == 0) {
                    // rule 2 = if number of digits is even
                    // create 2 new stones left side a new one and right side a new one
                    string stoneNumberString = Stones[i].Item1.ToString();
                    long leftNumber = long.Parse(stoneNumberString.Substring(0, stoneNumberString.Length / 2));
                    long rightNumber = long.Parse(stoneNumberString.Substring(stoneNumberString.Length / 2));

                    // insert right stone after original stone and set original to left Number
                    Stones.Insert(i + 1, (rightNumber, Stones[i].Item2));
                    Stones[i] = (leftNumber, Stones[i].Item2);
                } else {
                    Stones[i] = (Stones[i].Item1 * 2024, Stones[i].Item2);
                }
            }

            // sum together Stones with same Number stones
            SumStones();
        }

        private void SumStones() {
            for(int i = Stones.Count() - 1; i >= 0; i--) {
                for(int j = i - 1; j >= 0; j--) {
                    if(Stones[i].Item1 == Stones[j].Item1) {
                        Stones[i] = (Stones[i].Item1, Stones[i].Item2 + Stones[j].Item2);
                        Stones.RemoveAt(j);
                        i--;
                    }
                }
            }
        }

        public long GetStonesCount() {
            return Stones.Sum(stone => stone.Item2);
        }
    }
}