/**
*	created:		2013-4-29   17:25
*	filename: 		FKCallback
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace event
	{
		template <class ClassInstance, class ParamType>
		class TGenericCallback
		{
		public:
			TGenericCallback()
			{
				_function = 0;
			}
			
			typedef void (ClassInstance::*FunctionPointer)(ParamType param);
			
			virtual void Execute(ParamType param) const
			{
				if (_function) 
					(_instance->*_function)(param);
			}
			
			void SetCallback(	ClassInstance* instance, 
								FunctionPointer function)
			{
				_instance = instance;
				_function = function;
			}
			
			const ClassInstance* GetInstance()
			{
				return _instance;
			}
			
			const FunctionPointer GetFunction()
			{
				return _function;
			}
			
		private:
			ClassInstance*	_instance;
			FunctionPointer  _function;
		};
	}
}