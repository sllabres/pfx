
#pragma once

template <typename T>
class PingPong
{

	private:
		int updatedelayoffset;

	public:
		T minimum;
		T maximum;
		T value;
		T movestep;
		int updatedelay;
		bool isincreasing;


		PingPong(T Minimum, T Maximum, T StartValue)
		{
			minimum = Minimum;
			maximum = Maximum;
			value = StartValue;
			movestep = 1;
			updatedelay = 0;
			updatedelayoffset = 0;
			isincreasing = true;
		};

		void Update()
		{
			if( updatedelayoffset > 0 )
			{
				updatedelayoffset--;
				return;
			}

			if( isincreasing )
			{
				value += movestep;
				if( value >= maximum )
				{
					value = maximum;
					isincreasing = false;
				}
			} else {
				value -= movestep;
				if( value <= minimum )
				{
					value = minimum;
					isincreasing = true;
				}
			}

			updatedelayoffset = updatedelay;
		};

};
