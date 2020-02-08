# frozen_string_literal: true

class RemindersMailer < ApplicationMailer
  default from: MailFromHelper.from

  def remind_login(user_id)
    @user = User.find_by_id user_id

    return if @user.confirmed_at.nil?

    mail(
      to: @user.email,
      subject: '[BCEnvironmentApp] Login reminder'
    ) { |format|
      format.text
      format.html
    }
  end
end
