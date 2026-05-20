#include "../../RS-MET/Libraries/RobsJuceModules/rapt/rapt_templates.cpp"

template class RAPT::rsEnvelopeFollower2<double>;

template void RAPT::rsResampler<float, float>::transposeSinc(const float*, int, float*, int, float, float, bool);

template float RAPT::rsArrayTools::meanSquare<float>(const float*, int);